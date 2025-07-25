/*
 * SPDX-FileCopyrightText: 2019-2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BF0_HAL_QSPI_EXT_H
#define BF0_HAL_QSPI_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bf0_hal_qspi.h"


//#define FLASHC_TypeDef QSPI_TypeDef


/** @addtogroup BF0_HAL_Driver
  * @{
  */

/** @addtogroup SPI_FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPI_FLASHEx_Exported_Types SPI_FLASHEx Exported Types
  * @{
  */

/**
  * @brief  SPI_FLASHEx configure tyep
  */
#define FLASH_MAX_INSTANCE        (4)    /*!< Max spi flash hardware instance      */

/**
  * @brief  FLASHEx nor page size
  */
#define QSPI_NOR_PAGE_SIZE             (256)

/**
  * @brief  FLASHEx nor sector size
  */
#define QSPI_NOR_SECT_SIZE             (4096)

/**
  * @brief  FLASHEx nor block32 size
  */
#define QSPI_NOR_BLK32_SIZE            (0X8000)

/**
  * @brief  FLASHEx nor block64 size
  */
#define QSPI_NOR_BLK64_SIZE            (0X10000)

/**
 * @brief  FLASHEx max 128MB(1Gb) to make different flash address not accross
 *  we also use it to align local flash address by ~()
*/
#define FLASH_SUPPORT_MAX_SIZE        (0x8000000)

/**
 *@brief  FLASHEx When NOR FLASH larger than this size, 24 bits address not enough, need switch mode
 */
#define NOR_FLASH_MAX_3B_SIZE             (0x1000000)

/**
  * @brief  FLASHEx nand page size
  */
#define SPI_NAND_PAGE_SIZE                   (2048)

/**
  * @brief  FLASHEx max oob size
  */
#define SPI_NAND_MAXOOB_SIZE                   (128)

/**
  * @brief  FLASHEx nand block size
  */
#define SPI_NAND_BLK_SIZE                    (0x20000)

#define NAND_BUF_CPY_MODE                     (0)  /*!< NAND cache copy use sys memcpy     */

#define NAND_E_FAIL_BIT     (1<<2)        /*!< Erase fail bit in status register    */
#define NAND_P_FAIL_BIT     (1<<3)        /*!< Program fail bit in status register  */

#define SPI_MODE_NOR     (0)        /*!< function mode for nor flash      */
#define SPI_MODE_NAND    (1)        /*!< function mode for nand flash      */
#define SPI_MODE_PSRAM   (2)        /*!< function mode for psram      */
#define SPI_MODE_COUNT   (3)        /*!< current support function mode      */

/**
  * @brief  SPI_FLASHEx spi flash context
  */
typedef struct
{
    FLASH_HandleTypeDef         handle; /*!< flash handle     */
    uint32_t                    dev_id; /*!< flash device id     */
    uint8_t                     flash_mode; /*!< 0 nor, 1 nand, 2 psram      */
    uint8_t                     dual_mode;  /*!<  dual flash mode, 0 do not change, 1 single, 2 dual   */
    uint8_t                     cache_flag; /*!< manual clear  cache 1 or auto canch 2, default 2       */
    uint32_t                    base_addr;  /*!< flash base address     */
    uint32_t                    total_size; /*!< flash total size      */
    void                       *mtd; /*!<  mtd handle if needed     */
} QSPI_FLASH_CTX_T;


/**
  * @brief  QPSRAM Commands
  */
typedef enum
{
    BF0_QPSRAM_RD   = 0x03,   // Read
    BF0_QPSRAM_FRD  = 0x0b,   // Fast Read
    BF0_QPSRAM_QRD  = 0xeb,   // Quad Read
    BF0_QPSRAM_WR   = 0x02,   // Write
    BF0_QPSRAM_QWR  = 0x38,   // Quad Write
    BF0_QPSRAM_WRD  = 0x8b,   // Wrapped Read
    BF0_QPSRAM_WWR  = 0x82,   // Wrapped Write
    BF0_QPSRAM_MRR  = 0xb5,   // Mode Register Read
    BF0_QPSRAM_MRW  = 0xb1,   // Mode Register Write
    BF0_QPSRAM_QEN  = 0x35,   // Quad Mode Enable
    BF0_QPSRAM_QDIS = 0xf5,   // Quad Mode Disable
    BF0_QPSRAM_RSTE = 0x66,   // Reset Enable
    BF0_QPSRAM_RST  = 0x99,   // Reset
    BF0_QPSRAM_BLT  = 0xc0,   // Burst Length Toggle
    BF0_QPSRAM_RDID = 0x9f    // Read ID
} bf0_qspi_psram_cmd_t;

/**
  * @brief  FLASHEx check if is flash address
  * @param addr flash address
  * @retval true if success
  */
#define IS_SPI_FLASH_ADDR(addr)         (((((uint32_t)addr)&FLASH_BASE_ADDR) == FLASH_BASE_ADDR)    \
                                        || ((((uint32_t)addr)&FLASH2_BASE_ADDR) == FLASH2_BASE_ADDR) \
                                        || ((((uint32_t)addr)&FLASH3_BASE_ADDR) == FLASH3_BASE_ADDR))

/**
  * @brief  FLASHEx check if is non-DMA support RAM, such as ITCM/RETM address
  * @param addr flash address
  * @retval true if success
  */
#define IS_SPI_NONDMA_RAM_ADDR(addr)    (((((uint32_t)addr)&0xFFFF0000) == HPSYS_ITCM_BASE)    \
                                        || ((((uint32_t)addr)&0xFFFF0000) == HPSYS_RETM_BASE))


/**
  * @brief  FLASHEx check if source/dest address on the same flash
  * @param src source address
  * @param dst dest address
  * @retval true if success
  */
#define IS_SAME_FLASH_ADDR(src, dst) ((((((uint32_t)src)&FLASH_BASE_ADDR) == (((uint32_t)dst)&FLASH_BASE_ADDR)) && ((((uint32_t)src)&FLASH_BASE_ADDR) == FLASH_BASE_ADDR))    \
                                        || (((((uint32_t)src)&FLASH2_BASE_ADDR) == (((uint32_t)dst)&FLASH2_BASE_ADDR))&& ((((uint32_t)src)&FLASH2_BASE_ADDR) == FLASH2_BASE_ADDR)) \
                                        || (((((uint32_t)src)&FLASH3_BASE_ADDR) == (((uint32_t)dst)&FLASH3_BASE_ADDR))&& ((((uint32_t)src)&FLASH3_BASE_ADDR) == FLASH3_BASE_ADDR)))



/**
  * @brief  FLASHEx check if 64kb aligned
  * @param value flash address
  * @retval true if success
  */
#define ADDR_BLK64_ALIGN(value)     ((value&(QSPI_NOR_BLK64_SIZE-1))==0)


/**
  * @brief  FLASHEx check if 32kb aligned
  * @param value value address
  * @retval true if success
  */
#define ADDR_BLK32_ALIGN(value)     ((value&(QSPI_NOR_BLK32_SIZE-1))==0)


/**
  * @brief  FLASHEx check if sector aligned
  * @param value flash address
  * @retval true if success
  */
#define ADDR_SECT_ALIGN(value)     ((value&(QSPI_NOR_SECT_SIZE-1))==0)


/**
  * @brief  FLASHEx check if page aligned
  * @param value flash address
  * @retval true if success
  */
#define ADDR_PAGE_ALIGN(value)     ((value&(QSPI_NOR_PAGE_SIZE-1))==0)


/**
  * @brief  FLASHEx get address sector aligned down address
  * @param addr flash address
  * @retval address with sector aligned
  */
#define GET_SECTOR(addr)            ((addr)  & (~(QSPI_NOR_SECT_SIZE-1)))


/**
  * @brief  FLASHEx get sector aligned up size
  * @param size flash data size
  * @retval size with sector aligned
  */
#define GET_SIZE_BY_SECTOR(size)        (((size)+QSPI_NOR_SECT_SIZE-1)&(~(QSPI_NOR_SECT_SIZE-1)))


/**
  * @brief  FLASHEx get aligned down value
  * @param align alignment base, it should be ^2
  * @param value source value
  * @retval new value after aligned
  */
#define GET_ALIGNED_DOWN(align, value)      ((value) & (~((align)-1)))


/**
  * @brief  FLASHEx get aligned up value
  * @param align alignment base, it should be ^2
  * @param value source value
  * @retval new value after aligned
  */
#define GET_ALIGNED_UP(align, value)        (((value)+(align)-1) & (~(align-1)))


/**
  * @brief  FLASHEx check if aligned
  * @param align alignment base, it should be ^2
  * @param value source value
  * @retval true if success
  */
#define IS_ALIGNED(align, value)            (((value) & ((align)-1))==0)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPI_FLASHEx_Exported_Functions
  * @{
  */

/** @addtogroup SPI_FLASHEx_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Initial QSPI for flash mode
  * @param  ctx flash context
  * @param  cfg qspi configure parameter
  * @param  dma dma handler
  * @param  dma_cfg dma configure
  * @param  clk_div clock divider
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASH_Init(QSPI_FLASH_CTX_T *ctx, qspi_configure_t *cfg,
                                 DMA_HandleTypeDef *dma, struct dma_config *dma_cfg, uint16_t clk_div);


/**
  * @brief  Initial QSPI for psram
  * @param  hflash  QSPI handle
  * @param  cfg qspi configure parameter
  * @param  clk_div clock divider
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_PSRAM_Init(FLASH_HandleTypeDef *hflash, qspi_configure_t *cfg, uint16_t clk_div);

/**
  * @brief  FLASH deinitial
  * @param  hflash  SPI_FLASH handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASH_DeInit(FLASH_HandleTypeDef *hflash);

/**
  * @brief  Flash start dma transmit
  * @param  hflash  FLASH handle
  * @param  buf  data buffer
  * @param  write  1 for write, 0 for read
  * @param  len  data length
  * @retval hal status
*/
HAL_StatusTypeDef HAL_FLASH_DMA_START(FLASH_HandleTypeDef *hflash, char *buf, int write, uint32_t len);

/**
  * @brief  Flash wait dma transmit finish
  * @param  hflash  FLASH handle
  * @param  timeout  time out counter
  * @retval hal status
*/
HAL_StatusTypeDef HAL_FLASH_DMA_WAIT_DONE(FLASH_HandleTypeDef *hflash, uint32_t timeout);

/**
  * @brief  set alias
  * @param  fhandle  FLASH handle
  * @param  start start address
  * @param  len data length
  * @param  offset address offset
  * @retval none
*/
void HAL_FLASH_ALIAS_CFG(FLASH_HandleTypeDef *fhandle, uint32_t start, uint32_t len, uint32_t offset);

/**
  * @brief  set nonce
  * @param  fhandle  FLASH handle
  * @param  start start address
  * @param  end end address
  * @param  nonce nonce table
  * @retval none
*/
void HAL_FLASH_NONCE_CFG(FLASH_HandleTypeDef *fhandle, uint32_t start, uint32_t end, uint8_t *nonce);

/**
  * @brief  set AES
  * @param  fhandle  FLASH handle
  * @param  aes256 1 for AES 256, 0 FOR AES 128
  * @retval none
*/
void HAL_FLASH_AES_CFG(FLASH_HandleTypeDef *fhandle, uint8_t aes256);
/**
  * @}
  */

/** @addtogroup SPI_FLASHEx_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  nand flash read a page with address and size with page aligned
  * @param  handle  FLASH handle
  * @param  addr address to be read
  * @param  buff data buffer
  * @param  len data length
  * @retval read data length, 0 if write fail
*/
int HAL_NAND_READ_PAGE(FLASH_HandleTypeDef *handle, uint32_t addr, uint8_t *buff, uint32_t len);

/**
  * @brief  nand flash write a page with address and size aligned
  * @param  handle  FLASH handle
  * @param  addr address to be write
  * @param  buff data buffer
  * @param  len data length
  * @retval write data length, 0 if write fail
*/
int HAL_NAND_WRITE_PAGE(FLASH_HandleTypeDef *handle, uint32_t addr, const uint8_t *buff, uint32_t len);

/**
  * @brief  nand erase a block
  * @param  handle  FLASH handle
  * @param  addr start address to be erased
  * @retval 0 if success
*/
int HAL_NAND_ERASE_BLK(FLASH_HandleTypeDef *handle, uint32_t addr);

/**
  * @brief  nor flash write a page
  * @param  hflash  FLASH handle
  * @param  addr address to be write
  * @param  buf data buffer
  * @param  size data length
  * @retval write data length, 0 if write fail
*/
int HAL_QSPIEX_WRITE_PAGE(FLASH_HandleTypeDef *hflash, uint32_t addr, const uint8_t *buf, uint32_t size);

/**
  * @brief  fill one bye to flash to make remain size or address aligned
  * @param  hflash  FLASH handle
  * @param  addr address to be write
  * @param  buf data buffer
  * @param  prev need get previous byte from flash to refill
  * @retval write data length, 0 if write fail
*/
int HAL_QSPIEX_FILL_EVEN(FLASH_HandleTypeDef *hflash, uint32_t addr, uint8_t *buf, uint8_t prev);

/**
  * @brief  nor flash sector erase
  * @param  hflash  FLASH handle
  * @param  addr start address
  * @retval 0 if success
*/
int HAL_QSPIEX_SECT_ERASE(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
  * @brief  nor flash block32 erase
  * @param  hflash  FLASH handle
  * @param  addr start address
  * @retval 0 if success
*/
int HAL_QSPIEX_BLK32_ERASE(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
  * @brief  nor flash block 64 erase
  * @param  hflash  FLASH handle
  * @param  addr start address
  * @retval 0 if success
*/
int HAL_QSPIEX_BLK64_ERASE(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
  * @brief  nor flash chip erase
  * @param  hflash  FLASH handle
  * @retval 0 if success
*/
int HAL_QSPIEX_CHIP_ERASE(FLASH_HandleTypeDef *hflash);

/**
  * @}
  */


/** @addtogroup SPI_FLASHEx_Exported_Functions_Group3
  * @{
  */

/**
  * @brief  get qspi clock divider
  * @param  fhandle  FLASH handle
  * @retval clock divider
*/
uint32_t HAL_QSPI_GET_CLK(FLASH_HandleTypeDef *fhandle);

/**
  * @brief  get nor/nand manufactor id
  * @param  fhandle  FLASH handle
  * @retval device id
*/
int HAL_QSPI_READ_ID(FLASH_HandleTypeDef *fhandle);

/**
  * @brief  flash write
  * @param  hflash  FLASH handle
  * @param  addr flash address
  * @param  buf data buffer
  * @param  size data length
  * @retval 0 if  fail
*/
int HAL_QSPIEX_FLASH_WRITE(FLASH_HandleTypeDef *hflash, uint32_t addr, const uint8_t *buf, uint32_t size);

/**
  * @brief  flash erase
  * @param  hflash  FLASH handle
  * @param  addr flash address
  * @param  size data length
  * @retval 0 if success
*/
int HAL_QSPIEX_FLASH_ERASE(FLASH_HandleTypeDef *hflash, uint32_t addr, uint32_t size);

/**
  * @brief  flash reset
  * @param  hflash  FLASH handle
  * @retval none
*/
void HAL_QSPIEX_FLASH_RESET(FLASH_HandleTypeDef *hflash);

/**
  * @brief  Enable QSPI watch dog.
  * @retval 0 if success
*/
int HAL_QSPI_ENABLE_WDT();

/**
  * @brief  Enable/Disable NAND ECC.
  * @param  handle  FLASH handle
  * @param  en enable or disable
  * @retval 0 if success
*/
int HAL_NAND_CONF_ECC(FLASH_HandleTypeDef *handle, uint8_t en);

/**
  * @brief  Get ecc bit value
  * @param  handle  FLASH handle
  * @retval ecc bits value
*/
int HAL_NAND_GET_ECC_STATUS(FLASH_HandleTypeDef *handle);

/**
  * @brief  Check if last ecc error
  * @param  handle  FLASH handle
  * @retval 0 if no error
*/
int HAL_NAND_GET_ECC_RESULT(FLASH_HandleTypeDef *handle);

/**
  * @brief  Read nand flash with oob
  * @param  handle  FLASH handle
  * @param  addr address
  * @param  dbuff data buffer
  * @param  dlen date len
  * @param  oob_buf oob data buffer
  * @param  olen oob data zie
  * @retval data length
*/
int HAL_NAND_READ_WITHOOB(FLASH_HandleTypeDef *handle, uint32_t addr,
                          uint8_t *dbuff, uint32_t dlen, uint8_t *oob_buf, uint32_t olen);

/**
  * @brief  Write nand with oob, oob not emtpy only when ECC not enable !!!
  * @param  handle  FLASH handle
  * @param  addr address
  * @param  buff data buffer
  * @param  len date len
  * @param  oob_buf oob data buffer
  * @param  olen oob data zie
  * @retval data length
*/
int HAL_NAND_WRITE_WITHOOB(FLASH_HandleTypeDef *handle, uint32_t addr,
                           const uint8_t *buff, uint32_t len, const uint8_t *oob_buf, uint32_t olen);


/**
 * @brief  Enable/Disable NAND buf mode.
 * @param  handle  FLASH handle
 * @param  en enable or disable
 * @retval 0 if success
*/
int HAL_NAND_CONF_BUF(FLASH_HandleTypeDef *handle, uint8_t en);

/**
 * @brief  Enable/Disable NAND continue read mode with HWI.
 * @param  handle  FLASH handle
 * @param  addr page address to be load to cache
 * @param  en enable or disable
 * @param  data_len data length in byte
 * @retval 0 if success
*/
int HAL_NAND_SET_CONTINUE(FLASH_HandleTypeDef *handle, uint32_t addr, uint8_t en, uint32_t data_len);

/**
 * @brief  Enable/Disable NAND continue read mode for AHB.
 * @param  handle  FLASH handle
 * @param  addr page address to be load to cache
 * @param  en enable or disable
 * @retval 0 if success
*/
int HAL_NAND_AHB_CONTINUE(FLASH_HandleTypeDef *handle, uint32_t addr, uint8_t en);

/**
 * @brief  Get FLASH memory size in bytes.
 * @param  handle  FLASH handle
 * @retval memory size
*/
int HAL_QSPI_GET_MEMSIZE(FLASH_HandleTypeDef *handle);

/**
 * @brief  Get FLASH Status Register value.
 * @param  handle  FLASH handle
 * @retval status register value
*/
uint32_t HAL_QSPI_GET_SR(FLASH_HandleTypeDef *handle);

/**
 * @brief  Get FLASH unique ID, when XIP on flash, this cannot be called for this flash!!!
 * @param  hflash  FLASH handle
 * @param  uid unique id buffer
 * @param  len unique id length
 * @retval 0 if sucess
*/
int HAL_QSPI_GET_UID(FLASH_HandleTypeDef *hflash, uint32_t *uid, uint32_t len);

/**
 * @brief  Mark block as bad block or clear bad block.
 * @param  handle  FLASH handle
 * @param  blk block index
 * @param  bad set to bad or not
 * @retval 0 if sucess
*/
int HAL_NAND_MARK_BADBLK(FLASH_HandleTypeDef *handle, uint32_t blk, uint8_t bad);

/**
 * @brief  Check if this block is bad.
 * @param  handle  FLASH handle
 * @param  blk block index
 * @retval 0 if not bad block
*/
int HAL_NAND_GET_BADBLK(FLASH_HandleTypeDef *handle, uint32_t blk);


/**
 * @brief  Enable QE mode bit for nand.
 * @param  handle  FLASH handle
 * @param  en enable qual spi mode
 * @retval 0 if sucess
*/
int HAL_NAND_EN_QUAL(FLASH_HandleTypeDef *handle, uint8_t en);

/**
 * @brief  Lock security register, it's OTP spare, can not change after lock.
 * @param  hflash  FLASH handle
 * @param  addr security regiseter start address
 * @retval 0 if sucess
*/
int HAL_QSPI_LOCK_OTP(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
 * @brief  Erase security register.
 * @param  hflash  FLASH handle
 * @param  addr security regiseter start address
 * @retval 0 if sucess
*/
int HAL_QSPI_ERASE_OTP(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
 * @brief  Write security register.
 * @param  hflash  FLASH handle
 * @param  addr security regiseter address
 * @param  buf write data buffer
 * @param  size write data length
 * @retval write data size, 0 if fail
*/
int HAL_QSPI_WRITE_OTP(FLASH_HandleTypeDef *hflash, uint32_t addr, uint8_t *buf, uint32_t size);

/**
 * @brief  Read security register.
 * @param  hflash  FLASH handle
 * @param  addr security regiseter address
 * @param  buf read data buffer
 * @param  size read data length
 * @retval read data size, 0 if fail
*/
int HAL_QSPI_READ_OTP(FLASH_HandleTypeDef *hflash, uint32_t addr, uint8_t *buf, uint32_t size);

/**
 * @brief  Read OTP LB in status register.
 * @param  hflash  FLASH handle
 * @param  addr security regiseter address
 * @retval lock bits, 0xff if fail.
*/
uint8_t HAL_QSPI_GET_OTP_LB(FLASH_HandleTypeDef *hflash, uint32_t addr);

/**
 * @brief  Enable NAND OTP operation, include read/write.
 * @param  handle  FLASH handle
 * @param  otp otp mode or normal memory mode
 * @retval 0 if success.
*/
int HAL_NAND_SWITCH_OTP(FLASH_HandleTypeDef *handle, uint8_t otp);

/**
 * @brief  Lock NAND OTP erea.
 * @param  handle  FLASH handle
 * @retval 0 if success.
*/
int HAL_NAND_LOCK_OTP(FLASH_HandleTypeDef *handle);

void HAL_QSPIEX_FLASH_RESET2(QSPI_TypeDef *hmpi);

/**
 * @brief  Get page size for nand.
 * @param  handle  FLASH handle
 * @retval nand page size, 0 if fail
*/
uint32_t HAL_NAND_PAGE_SIZE(FLASH_HandleTypeDef *handle);

/**
 * @brief  Get block size for nand.
 * @param  handle  FLASH handle
 * @retval nand block size, 0 if fail
*/
uint32_t HAL_NAND_BLOCK_SIZE(FLASH_HandleTypeDef *handle);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* BF0_HAL_QSPI_EXT_H */