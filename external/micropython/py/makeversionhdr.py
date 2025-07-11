"""
Generate header file with macros defining MicroPython version info.

This script works with Python 2.6, 2.7, 3.3 and 3.4.
"""

from __future__ import print_function

import sys
import os
import datetime
import subprocess


def get_version_info_from_git():
    # Python 2.6 doesn't have check_output, so check for that
    try:
        subprocess.check_output
        subprocess.check_call
    except AttributeError:
        return None

    # Note: git describe doesn't work if no tag is available
    try:
        git_tag = subprocess.check_output(
            ["git", "describe", "--always", "--match", "v[1-9].*"],
            stderr=subprocess.STDOUT,
            universal_newlines=True,
        ).strip()
    except subprocess.CalledProcessError as er:
        if er.returncode == 128:
            # git exit code of 128 means no repository found
            return None
        git_tag = ""
    except OSError:
        return None
    try:
        git_hash = subprocess.check_output(
            ["git", "rev-parse", "--short", "HEAD"],
            stderr=subprocess.STDOUT,
            universal_newlines=True,
        ).strip()
    except subprocess.CalledProcessError:
        git_hash = "unknown"
    except OSError:
        return None

    return git_tag, git_hash


def get_version_info_from_docs_conf():
    with open(os.path.join(os.path.dirname(sys.argv[0]), "..", "docs", "conf.py")) as f:
        for line in f:
            if line.startswith("version = release = '"):
                ver = line.strip().split(" = ")[2].strip("'")
                git_tag = "v" + ver
                return git_tag, "<no hash>"
    return None


def make_version_header(filename):
    # Get version info using git, with fallback to docs/conf.py
    info = get_version_info_from_git()
    if info is None:
        info = get_version_info_from_docs_conf()

    git_tag, git_hash = info

    # Generate the file with the git and version info
    file_data = """\
// This file was generated by py/makeversionhdr.py
#define MICROPY_GIT_TAG "%s"
#define MICROPY_GIT_HASH "%s"
#define MICROPY_BUILD_DATE "%s"
""" % (
        git_tag,
        git_hash,
        datetime.date.today().strftime("%Y-%m-%d"),
    )

    # Check if the file contents changed from last time
    write_file = True
    if os.path.isfile(filename):
        with open(filename, "r") as f:
            existing_data = f.read()
        if existing_data == file_data:
            write_file = False

    # Only write the file if we need to
    if write_file:
        print("GEN %s" % filename)
        with open(filename, "w") as f:
            f.write(file_data)


if __name__ == "__main__":
    make_version_header(sys.argv[1])
