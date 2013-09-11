################################################################################
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or distribute
# this software, either in source code form or as a compiled binary, for any
# purpose, commercial or non-commercial, and by any means.
#
# In jurisdictions that recognize copyright laws, the author or authors of this
# software dedicate any and all copyright interest in the software to the
# public domain. We make this dedication for the benefit of the public at large
# and to the detriment of our heirs and successors. We intend this dedication
# to be an overt act of relinquishment in perpetuity of all present and future
# rights to this software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>
################################################################################

ifeq ($(PLATFORM),windows)
  ifneq ($(TARGET_PLATFORM),windows)
    $(error No cross-compilation support for '$(TARGET_PLATFORM)' on Windows.)
  else
    CC := gcc
    LIB_PREFIX :=
    LIB_SUFFIX := .lib
    SHARED_LIB_PREFIX :=
    SHARED_LIB_SUFFIX := .dll
  endif
endif

ifeq ($(PLATFORM),macosx)
  ifneq ($(TARGET_PLATFORM),macosx)
    $(error No cross-compilation support for '$(TARGET_PLATFORM)' on MacOSX.)
  else
    CC := clang
    LIB_PREFIX := lib
    LIB_SUFFIX := .a
    SHARED_LIB_PREFIX := lib
    SHARED_LIB_SUFFIX := .dylib
  endif
endif

ifeq ($(PLATFORM),linux)
  ifneq ($(TARGET_PLATFORM),linux)
    $(error No cross-compilation support for '$(TARGET_PLATFORM)' on Linux.)
  else
    CC := gcc
    LIB_PREFIX := lib
    LIB_SUFFIX := .a
    SHARED_LIB_PREFIX := lib
    SHARED_LIB_SUFFIX := .so
  endif
endif
