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

# See ./configure
-include build/config.mk

################################################################################

include build/platform.mk

ifndef TARGET_PLATFORM
	TARGET_PLATFORM := $(PLATFORM)
endif

include build/toolchain.mk
include build/architecture.mk

################################################################################

CFLAGS       := -std=c++98 -pedantic -Wall -Wextra -Wfloat-equal -Wshadow \
                -Wunsafe-loop-optimizations -Wpointer-arith -Wcast-qual \
                -Wcast-align -Wmissing-field-initializers -Wpacked \
                -Wpadded -Wredundant-decls -Wunreachable-code -Winline -fPIC
INCLUDES     := -Iinclude
LDFLAGS      :=
DEPENDENCIES :=

################################################################################

ifeq ($(PARANOID),yes)
  CFLAGS += -DAGL_PARANOID
endif

ifeq ($(DEBUG),yes)
  CFLAGS += -g -DAGL_DEBUG -D_DEBUG
else
  CFLAGS += -O3 -DAGL_RELEASE -DNDEBUG
endif

ifeq ($(TARGET_PLATFORM),windows)
  CFLAGS += -D_WIN32 -DWINVER=0x500
endif

################################################################################

SRC_DIR := src
BIN_DIR := bin
LIB_DIR := lib
OBJ_DIR := obj
COMMIT  := $(shell git rev-parse HEAD)

################################################################################

AGL := $(BIN_DIR)/$(SHARED_LIB_PREFIX)agl$(SHARED_LIB_SUFFIX)

all: $(AGL)

clean:
	@rm -R -f $(BIN_DIR)
	@rm -R -f $(LIB_DIR)
	@rm -R -f $(OBJ_DIR)

SOURCES := $(shell find $(SRC_DIR) -name '*.cc')
OBJECTS := $(OBJ_DIR)/agl/atomic.o $(OBJ_DIR)/agl/shared_lib.o $(OBJ_DIR)/agl.o
# OBJECTS := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.cc=%.o)))

ifeq ($(TARGET_PLATFORM),windows)
  OBJECTS += $(OBJ_DIR)/agl.d3d9.o
endif

-include $(OBJECTS:.o=.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	@$(CC) $(CFLAGS) $(INCLUDES) -DAGL_COMPILING -c $< -o $@
	@$(CC) $(CFLAGS) $(INCLUDES) -DAGL_COMPILING -MM -MT $@ -c $< > $(patsubst %.o,%.d,$@)

$(AGL): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
	@$(CC) $(LDFLAGS) -shared -o $@ $^ $(DEPENDENCIES)
