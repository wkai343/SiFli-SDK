/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2014 - 2022 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************
*
*    The GPL License (GPL)
*
*    Copyright (C) 2014 - 2022 Vivante Corporation
*
*    This program is free software; you can redistribute it and/or
*    modify it under the terms of the GNU General Public License
*    as published by the Free Software Foundation; either version 2
*    of the License, or (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*****************************************************************************
*
*    Note: This software is released under dual MIT and GPL licenses. A
*    recipient may use this file under the terms of either the MIT license or
*    GPL License. If you wish to use only one license not the other, you can
*    indicate your decision by deleting one of the above license notices in your
*    version of this file.
*
*****************************************************************************/

#include "board.h"
#include "vg_lite_platform.h"
#include "vg_lite_kernel.h"
#include "vg_lite_hal.h"
#include "vg_lite_hw.h"

#if !_BAREMETAL
    #include "os_adaptor.h"
#else
    #include "xil_cache.h"
    #include "sleep.h"
#endif

#include <stdarg.h>

static void sleep(uint32_t msec)
{
    os_delay(msec);
}

static    uint32_t    registerMemBase    = V2D_GPU_BASE;

/* If bit31 is activated this indicates a bus error */
#define IS_AXI_BUS_ERR(x) ((x)&(1U << 31))

#define HEAP_NODE_USED  0xABBAF00D

#undef MAX_CONTIGUOUS_SIZE
#define MAX_CONTIGUOUS_SIZE (VGLITE_CONT_MEM_SIZE*1024)

#ifdef USING_VGLITE_STATIC_CONT_MEM
    ALIGN(64)
    static uint8_t vglite_cont_mem[MAX_CONTIGUOUS_SIZE];
    volatile void *contiguousMem = vglite_cont_mem;
#else
volatile void* contiguousMem[VG_SYSTEM_RESERVE_COUNT] = {
    [0 ... VG_SYSTEM_RESERVE_COUNT - 1] = NULL
};
#endif /* USING_VGLITE_STATIC_CONT_MEM */

uint32_t gpuMemBase[VG_SYSTEM_RESERVE_COUNT] = {
    [0 ... VG_SYSTEM_RESERVE_COUNT - 1] = 0
};


static uint32_t heap_size[VG_SYSTEM_RESERVE_COUNT] = {
    [0 ... VG_SYSTEM_RESERVE_COUNT - 1] = MAX_CONTIGUOUS_SIZE
};

void __attribute__((weak)) vg_lite_bus_error_handler();

void vg_lite_init_mem(vg_module_parameters_t *param)
{
    uint32_t i;

    registerMemBase = param->register_mem_base;

    for (i = 0; i< VG_SYSTEM_RESERVE_COUNT; i++) {
        gpuMemBase[i]      = param->gpu_mem_base[i];
        contiguousMem[i]   = param->contiguous_mem_base[i];
        heap_size[i]       = param->contiguous_mem_size[i];
    }
}

/* Implementation of list. ****************************************/
#define INIT_LIST_HEAD(entry) \
        (entry)->next = (entry);\
        (entry)->prev = (entry);

/* Add the list item in front of "head". */
static inline void add_list(list_head_t *to_add, list_head_t *head)
{
    /* Link the new item. */
    to_add->next = head;
    to_add->prev = head->prev;

  /* Modify the neighbor. */
    head->prev = to_add;
    if (to_add->prev != NULL) {
        to_add->prev->next = to_add;
    }
}

/* Remove an entry out of the list. */
static inline void delete_list(list_head_t *entry)
{
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;
    }
    if (entry->next != NULL) {
        entry->next->prev = entry->prev;
    }
}

/* End of list implementation. ***********/
static inline void _memset(void *mem, unsigned char value, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        ((unsigned char *)mem)[i] = value;
    }
}

struct memory_heap {
    uint32_t free;
    list_head_t list;
};

struct mapped_memory {
    void *logical;
    uint32_t physical;
    int page_count;
    struct page **pages;
};

struct vg_lite_device {
    /* void * gpu; */
    uint32_t register_base;    /* Always use physical for register access in RTOS. */
    /* struct page * pages; */
    volatile void *contiguous[VG_SYSTEM_RESERVE_COUNT];
    unsigned int order;
    unsigned int heap_size[VG_SYSTEM_RESERVE_COUNT];
    void *virtual[VG_SYSTEM_RESERVE_COUNT];
    uint32_t physical[VG_SYSTEM_RESERVE_COUNT];
    uint32_t size[VG_SYSTEM_RESERVE_COUNT];
    struct memory_heap heap[VG_SYSTEM_RESERVE_COUNT];
    int irq_enabled;
    volatile uint32_t int_flags;
#if _BAREMETAL
    /* wait_queue_head_t int_queue; */
    xSemaphoreHandle int_queue;
#else
    /* wait_queue_head_t int_queue; */
    OS_SEM_DECLAR(int_queue);
#endif
    void * device;
    int registered;
    int major;
    struct class * class;
    int created;
    vg_lite_gpu_execute_state_t gpu_execute_state;
};

struct client_data {
    struct vg_lite_device * device;
    struct vm_area_struct * vm;
    void * contiguous_mapped;
};

static struct vg_lite_device Device, * device;

void vg_lite_set_gpu_execute_state(vg_lite_gpu_execute_state_t state)
{
    device->gpu_execute_state = state;
}

vg_lite_error_t vg_lite_hal_allocate(uint32_t size, void **memory)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;

#if _BAREMETAL
    /* Alloc is not supported in BAREMETAL / DDRLESS. */
    *memory = NULL;
    error  = VG_LITE_NOT_SUPPORT;
#else
    /* TODO: Allocate some memory. No more kernel mode in RTOS. */
    *memory = malloc(size);
    if (NULL == *memory)
        error = VG_LITE_OUT_OF_MEMORY;
#endif

    return error;
}

vg_lite_error_t vg_lite_hal_free(void *memory)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    
#if !_BAREMETAL
    /* TODO: Free some memory. No more kernel mode in RTOS. */
    free(memory);
#endif

    return error;
}

void vg_lite_hal_delay(uint32_t ms)
{
    sleep(ms);
}

void vg_lite_hal_barrier(void)
{
     /*Memory barrier. */
#if _BAREMETAL
     Xil_DCacheFlush();
#else
    __asm("DSB");
#endif
}

static int vg_lite_init(void);
void vg_lite_hal_initialize(void)
{
    /* TODO: Turn on the power. */
    HAL_RCC_EnableModule(RCC_MOD_GPU);
    vg_lite_init();
    /* TODO: Turn on the clock. */
}

void vg_lite_hal_deinitialize(void)
{
    /* TODO: Remove clock. */
    os_sem_delete(device->int_queue);
    /* TODO: Remove power. */
    //HAL_RCC_DisableModule(RCC_MOD_GPU);    
}

static int split_node(heap_node_t * node, unsigned long size)
{
    /* TODO: the original is linux specific list based, needs rewrite.
    */
    heap_node_t * split;

    /* Allocate a new node. */
    vg_lite_hal_allocate(sizeof(heap_node_t), (void **)&split);
    if (split == NULL)
        return -1;

    /* Fill in the data of this node of the remaning size. */
    split->offset = node->offset + size;
    split->size = node->size - size;
    split->status = 0;

    /* Add the new node behind the current node. */
    add_list(&split->list, &node->list);

    /* Adjust the size of the current node. */
    node->size = size;
    return 0;
}

void vg_lite_hal_print(char *format, ...)
{
    static char buffer[128];
    va_list args;
    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer) - 1, format, args);
    buffer[sizeof(buffer) - 1] = 0;
    //printf(buffer);

    va_end(args);
}

void vg_lite_hal_trace(char *format, ...)
{
    static char buffer[128];
    va_list args;
    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer) - 1, format, args);
    buffer[sizeof(buffer) - 1] = 0;
    //printf(buffer);

    va_end(args);
}

const char* vg_lite_hal_Status2Name(vg_lite_error_t status)
{
    switch (status) {
    case VG_LITE_SUCCESS:
        return "VG_LITE_SUCCESS";
    case VG_LITE_INVALID_ARGUMENT:
        return "VG_LITE_INVALID_ARGUMENT";
    case VG_LITE_OUT_OF_MEMORY:
        return "VG_LITE_OUT_OF_MEMORY";
    case VG_LITE_NO_CONTEXT:
        return "VG_LITE_NO_CONTEXT";
    case VG_LITE_TIMEOUT:
        return "VG_LITE_TIMEOUT";
    case VG_LITE_OUT_OF_RESOURCES:
        return "VG_LITE_OUT_OF_RESOURCES";
    case VG_LITE_GENERIC_IO:
        return "VG_LITE_GENERIC_IO";
    case VG_LITE_NOT_SUPPORT:
        return "VG_LITE_NOT_SUPPORT";
    case VG_LITE_ALREADY_EXISTS:
        return "VG_LITE_ALREADY_EXISTS";
    case VG_LITE_NOT_ALIGNED:
        return "VG_LITE_NOT_ALIGNED";
    case VG_LITE_FLEXA_TIME_OUT:
        return "VG_LITE_FLEXA_TIME_OUT";
    case VG_LITE_FLEXA_HANDSHAKE_FAIL:
        return "VG_LITE_FLEXA_HANDSHAKE_FAIL";
    case VG_LITE_SYSTEM_CALL_FAIL:
        return "VG_LITE_SYSTEM_CALL_FAIL";
    default:
        return "nil";
    }
}

vg_lite_error_t vg_lite_hal_allocate_contiguous(unsigned long size, vg_lite_vidmem_pool_t pool, void **logical, void **klogical, uint32_t *physical, void **node)
{
    unsigned long aligned_size;
    heap_node_t *pos;

    /* Judge if it exceeds the range of pool */
    if (pool >= VG_SYSTEM_RESERVE_COUNT)
        pool = VG_SYSTEM_RESERVE_COUNT - 1;

    /* Align the size to 64 bytes. */
    aligned_size = (size + 63) & ~63;

    //rt_kprintf("[%d]free:%d,%d\n", pool, device->heap[pool].free, size);

    /* Check if there is enough free memory available. */
    if (aligned_size > device->heap[pool].free) {
        return VG_LITE_OUT_OF_MEMORY;
    }

    /* Walk the heap backwards. */
    for (pos = (heap_node_t *)device->heap[pool].list.prev;
                 &pos->list != &device->heap[pool].list;
                 pos = (heap_node_t*) pos->list.prev) {
        /* Check if the current node is free and is big enough. */
        if (pos->status == 0 && pos->size >= aligned_size) {
            /* See if we the current node is big enough to split. */
                if (0 != split_node(pos, aligned_size))
                {
                    return VG_LITE_OUT_OF_RESOURCES;
                }
            /* Mark the current node as used. */
            pos->status = 0xABBAF00D;

            /*  Return the logical/physical address. */
            /* *logical = (uint8_t *) private_data->contiguous_mapped + pos->offset; */
            *logical = (uint8_t *)device->virtual[pool] + pos->offset;
            *klogical = *logical;
            *physical = gpuMemBase[pool] + (uint32_t)(*logical);/* device->physical + pos->offset; */

            /* Mark which pool the pos belong to */
            pos->pool = pool;

            device->heap[pool].free -= aligned_size;

            *node = pos;
            return VG_LITE_SUCCESS;
        }
    }

    /* Out of memory. */
    return VG_LITE_OUT_OF_MEMORY;
}

void vg_lite_hal_free_contiguous(void *memory_handle)
{
    /* TODO: no list available in RTOS. */
    heap_node_t *pos, *node;
    vg_lite_vidmem_pool_t pool;

    /* Get pointer to node. */
    node = memory_handle;

    if (node->status != 0xABBAF00D) {
        return;
    }

    /* Determine which pool the node belongs to */
    pool = node->pool;

    /* Mark node as free. */
    node->status = 0;

    /* Add node size to free count. */
    device->heap[pool].free += node->size;

    /* Check if next node is free. */
    pos = node;
    for (pos = (heap_node_t *)pos->list.next;
         &pos->list != &device->heap[pool].list;
         pos = (heap_node_t *)pos->list.next) {
        if (pos->status == 0) {
            /* Merge the nodes. */
            node->size += pos->size;
            if (node->offset > pos->offset)
                node->offset = pos->offset;
            /* Delete the next node from the list. */
            delete_list(&pos->list);
            vg_lite_hal_free(pos);
        }
        break;
    }

    /* Check if the previous node is free. */
    pos = node;
    for (pos = (heap_node_t *)pos->list.prev;
         &pos->list != &device->heap[pool].list;
         pos = (heap_node_t *)pos->list.prev) {
        if (pos->status == 0) {
            /* Merge the nodes. */
            pos->size += node->size;
            if (pos->offset > node->offset)
                pos->offset = node->offset;
            /* Delete the current node from the list. */
            delete_list(&node->list);
            vg_lite_hal_free(node);
        }
        break;
    }

    /* when release command buffer node and ts buffer node to exit,release the linked list*/
    /* if(device->heap[pool].list.next == device->heap[pool].list.prev) {
        delete_list(&pos->list);
        vg_lite_hal_free(pos);
    }*/
}

void vg_lite_hal_free_os_heap(void)
{
    struct heap_node *pos, *n;
    uint32_t i;

    /* Check for valid device. */
    if (device != NULL) {
        /* Process each node. */
        for (i = 0; i < VG_SYSTEM_RESERVE_COUNT; i++) {
            for (pos = (heap_node_t *)device->heap[i].list.next,
                 n = (heap_node_t *)pos->list.next;
                 &pos->list != &device->heap[i].list;
                 pos = n, n = (heap_node_t *)n->list.next) {
                /* Remove it from the linked list. */
                delete_list(&pos->list);
                /* Free up the memory. */
                vg_lite_hal_free(pos);
            }
        }
    }
}

volatile uint32_t peek_addr;
/* Portable: read register value. */
uint32_t vg_lite_hal_peek(uint32_t address)
{
    peek_addr = (uint32_t)(device->register_base + address);
    /* Read data from the GPU register. */
    return (uint32_t) (*(volatile uint32_t *) (device->register_base + address));
}

/* Portable: write register. */
void vg_lite_hal_poke(uint32_t address, uint32_t data)
{
    /* Write data to the GPU register. */
    uint32_t *LocalAddr = (uint32_t *)(device->register_base + address);
    *LocalAddr = data;
}

vg_lite_error_t vg_lite_hal_query_mem(vg_lite_kernel_mem_t *mem)
{
    if(device != NULL){
        mem->bytes  = device->heap[mem->pool].free;
        return VG_LITE_SUCCESS;
    }
    mem->bytes = 0;
    return VG_LITE_NO_CONTEXT;
}

vg_lite_error_t vg_lite_hal_map_memory(vg_lite_kernel_map_memory_t *node)
{
    node->logical = (void *)node->physical;
    return VG_LITE_SUCCESS;
}

vg_lite_error_t vg_lite_hal_unmap_memory(vg_lite_kernel_unmap_memory_t *node)
{
    return VG_LITE_SUCCESS;
}

void __attribute__((weak)) vg_lite_bus_error_handler()
{
    /*
     * Default implementation of the bus error handler does nothing. Application
     * should override this handler if it requires to be notified when a bus
     * error event occurs.
     */
    OS_ASSERT(false);
    return;
}

void V2D_GPU_IRQHandler(void) 
{
    os_interrupt_enter();

    vg_lite_IRQHandler();

    os_interrupt_exit();
}

void vg_lite_IRQHandler(void)
{
    uint32_t flags = vg_lite_hal_peek(VG_LITE_INTR_STATUS);

    if (flags) {
        /* Combine with current interrupt flags. */
        device->int_flags |= flags;

        /* Wake up any waiters. */
        if (device->int_queue) {
            os_sem_release(device->int_queue);
        }
    }
}

int32_t vg_lite_hal_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value)
{
#if _BAREMETAL
    uint32_t int_status=0;
    int_status = vg_lite_hal_peek(VG_LITE_INTR_STATUS);
    (void)value;

    while (int_status==0){
        int_status = vg_lite_hal_peek(VG_LITE_INTR_STATUS);
        //usleep(1);
    }

    if (value) {
        *value = int_status & mask;
        if (IS_AXI_BUS_ERR(*value)) {
            vg_lite_bus_error_handler();
        }
    }
    return 1;
#else /*for rt500*/
    if (device->int_queue) {
        if (os_sem_take(device->int_queue, timeout) == 0) {
            if (value != NULL) {
                *value = device->int_flags & mask;
                if (IS_AXI_BUS_ERR(*value))
                {
                    vg_lite_bus_error_handler();
                }
            }
            device->int_flags = 0;
            return 1;
        }
    }
    return 0;
#endif
}

vg_lite_error_t vg_lite_hal_memory_export(int32_t *fd)
{
    return VG_LITE_SUCCESS;
}


void * vg_lite_hal_map(uint32_t flags, uint32_t bytes, void *logical, uint32_t physical, int32_t dma_buf_fd, uint32_t *gpu)
{
    (void) flags;
    (void) bytes;
    (void) logical;
    (void) physical;
    (void) dma_buf_fd;
    (void) gpu;

    *gpu = (uint32_t)logical;
    return (void *)logical;
}

void vg_lite_hal_unmap(void * handle)
{

    (void) handle;
}

vg_lite_error_t vg_lite_hal_operation_cache(void *handle, vg_lite_cache_op_t cache_op)
{
    (void) handle;
    (void) cache_op;

    return VG_LITE_SUCCESS;
}

static void vg_lite_exit(void)
{
    heap_node_t *pos;
    heap_node_t *n;
    uint32_t i;

    /* Check for valid device. */
    if (device != NULL) {
        /* TODO: unmap register mem should be unnecessary. */
        device->register_base = 0;

        for (i = 0; i < VG_SYSTEM_RESERVE_COUNT; i++) {
            /* Process each node. */
            for (pos = (heap_node_t *)device->heap[i].list.next, n = (heap_node_t *)pos->list.next;
                 &pos->list != &device->heap[i].list;
                 pos = n, n = (heap_node_t *)n->list.next) {
                /* Remove it from the linked list. */
                delete_list(&pos->list);

                /* Free up the memory. */
                vg_lite_hal_free(pos);
            }
        }

        /* Free up the device structure. */
        vg_lite_hal_free(device);
    }
}

static int vg_lite_init(void)
{
    heap_node_t *node;
    OS_SEM_DECLAR(int_queue);
    uint32_t i;

    /* Initialize memory and objects ***************************************/
    /* Create device structure. */
    device = &Device;

    /* Zero out the enture structure. */
    _memset(device, 0, sizeof(struct vg_lite_device));

    /* Setup register memory. **********************************************/
    device->register_base = registerMemBase;

    
    /* Initialize contiguous memory. ***************************************/
    /* Allocate the contiguous memory. */
    for (i = 0; i < VG_SYSTEM_RESERVE_COUNT; i++) {
        device->heap_size[i] = heap_size[i];
        device->contiguous[i] = (volatile void *)contiguousMem[i];
        /* Make 64byte aligned. */
        while ((((uint32_t)device->contiguous[i]) & 63) != 0)
        {
            device->contiguous[i] = ((unsigned char *)device->contiguous[i]) + 4;
            device->heap_size[i] -= 4;
        }

        /* Check if we allocated any contiguous memory or not. */
        if (device->contiguous[i] == NULL) {
            vg_lite_exit();
            return -1;
        }

        device->virtual[i] = (void *)device->contiguous[i];
        device->physical[i] = gpuMemBase[i] + (uint32_t)device->virtual[i];
        device->size[i] = device->heap_size[i];

        /* Create the heap. */
        INIT_LIST_HEAD(&device->heap[i].list);
        device->heap[i].free = device->size[i];

        vg_lite_hal_allocate(sizeof(heap_node_t), (void **)&node);
        if (node == NULL) {
            vg_lite_exit();
            return -1;
        }
        node->offset = 0;
        node->size = device->size[i];
        node->status = 0;
        add_list(&node->list, &device->heap[i].list);
    }

#if !_BAREMETAL /*for rt500*/
    int_queue = os_sem_create("vglite", 0);
    device->int_queue = int_queue;
    device->int_flags = 0;
#endif
    /* Success. */
    return 0;
}
