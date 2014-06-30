#===-- mk/clang.mk ---------------------------------------------------------===#
#
#  Abstract Graphics Library (AGL)
#
#  This file is distributed under the terms described in LICENSE.
#
#  Author(s):
#
#    * Michael Williams <mwilliams@bitbyte.ca>
#
#===------------------------------------------------------------------------===#

## \file mk/clang.mk
## \brief Provides the standardized toolchain interface for Clang.
##

ifndef _AGL_BUILD_CLANG_MK_
_AGL_BUILD_CLANG_MK_ := 1

include mk/detect/platform.mk
include mk/detect/architecture.mk

#===------------------------------------------------------------------------===#
# Check for support
#

# Check that the host platform supports the toolchain.
ifeq ($(HOST_PLATFORM),windows-cygwin)
  $(error Compilation on 'windows-cygwin' with 'clang' is not supported.)
endif
ifeq ($(HOST_PLATFORM),windows-mingw)
  # Supported.
endif
ifeq ($(HOST_PLATFORM),macosx)
  # Supported.
endif
ifeq ($(HOST_PLATFORM),linux)
  # Supported.
endif

# And check that the toolchain can compile for the target platform.
ifneq ($(TARGET_PLATFORM),$(HOST_PLATFORM))
  $(error Cross-compilation support on '$(HOST_PLATFORM)' with 'clang' to '$(TARGET_PLATFORM)' is not supported.)
endif

# And check that we can target the specified architecture.
ifeq ($(TARGET_ARCHITECTURE),x86)
  # Supported.
endif
ifeq ($(TARGET_ARCHITECTURE),x86-64)
  # Supported.
endif
ifeq ($(TARGET_ARCHITECTURE),arm)
  $(error Compilation on '$(HOST_PLATFORM)' with 'clang' targeting 'arm' is not supported.)
endif

#===------------------------------------------------------------------------===#
# Define CFLAGS, LDFLAGS, and ARFLAGS
#

CFLAGS  := -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual \
           -Wcast-align -Wmissing-field-initializers -Wpacked -Wpadded \
           -Wredundant-decls -Wunreachable-code -Winline

LDFLAGS :=

ARFLAGS :=

ifeq ($(TARGET_ARCHITECTURE),x86)
  CFLAGS += -m32
  LDFLAGS += -m32
endif
ifeq ($(TARGET_ARCHITECTURE),x86-64)
  CFLAGS += -m64
  LDFLAGS += -m64
endif

#===------------------------------------------------------------------------===#
# Implement the standardized interface
#

cc                           = clang -std=gnu99 -pedantic $(CFLAGS)
c++                          = clang++ -std=gnu++0x -pedantic $(CFLAGS)
cc-input                     = -c "$(1)"
cc-output                    = -o "$(1)"
cc-includes                  = -I"$(1)"
cc-define                    = -D$(1)
cc-define-str                = -D$(1)="\"$(2)\""
cc-position-independent-code = -fPIC
cc-generate-dependencies     = -MM -MT"$(1)"
cc-debug                     = -g
cc-development               = -g
cc-release                   = -O3

ar                           = ar -rcs $(ARFLAGS)
ar++                         = ar -rcs $(ARFLAGS)
ar-input                     = "$(1)"
ar-output                    = -o "$(1)"
ar-debug                     =
ar-development               =
ar-release                   =

ld                           = clang $(LDFLAGS)
ld++                         = clang++ $(LDFLAGS)
ld-input                     = "$(1)"
ld-output                    = -o "$(1)"
ld-libraries                 = -L"$(1)"
ld-link                      = -l$(1)
ld-shared                    = -shared
ld-debug                     =
ld-development               =
ld-release                   =

endif # _AGL_BUILD_CLANG_MK_
