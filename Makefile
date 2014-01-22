################################################################################
##                                                                            ##
## This file is part of the Abstract Graphics Library.                        ##
##                                                                            ##
## Author(s):                                                                 ##
##                                                                            ##
##   Michael Williams <devbug@bitbyte.ca>                                     ##
##                                                                            ##
## See LICENSE.md for licensing information.                                  ##
##                                                                            ##
################################################################################
## Makefile                                                                   ##
##  Specifies all build rules for AGL.                                        ##
################################################################################

-include build/config
ifndef _AGL_BUILD_CONFIG_
  $(error Please ./configure first.)
endif

include build/toolchain.mk
include build/platform.mk
include build/architecture.mk
include build/detect/platform.mk
include build/detect/architecture.mk

################################################################################
# Binary, library, object, and source directories:                             #
################################################################################

BIN_DIR := bin
LIB_DIR := lib
OBJ_DIR := obj
SRC_DIR := src

################################################################################
# Debugging and optimization:                                                  #
################################################################################

ifeq ($(CONFIGURATION),debug)
  CFLAGS  += $(call cc-define,AGL_CONFIGURATION=1) $(call cc-debug)
  LDFLAGS += $(call ld-debug)
  ARFLAGS += $(call ar-debug)
endif
ifeq ($(CONFIGURATION),development)
  CFLAGS  += $(call cc-define,AGL_CONFIGURATION=2) $(call cc-development)
  LDFLAGS += $(call ld-development)
  ARFLAGS += $(call ar-development)
endif
ifeq ($(CONFIGURATION),release)
  CFLAGS  += $(call cc-define,AGL_CONFIGURATION=3) $(call cc-release)
  LDFLAGS += $(call ld-release)
  ARFLAGS += $(call ar-release)
endif

################################################################################
# Rules:                                                                       #
################################################################################

ifeq ($(LINKAGE),static)
  AGL := $(LIB_DIR)/$(STATIC_LIB_PREFIX)agl$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(LINKAGE),dynamic)
  AGL := $(BIN_DIR)/$(SHARED_LIB_PREFIX)agl$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

.PHONY: all docs clean

all: $(AGL)

docs:
	@echo "[DOXYGEN] Doxyfile"
	@doxygen Doxyfile

clean:
	@echo "Cleaning..."
	@rm -R -f $(BIN_DIR)
	@rm -R -f $(LIB_DIR)
	@rm -R -f $(OBJ_DIR)
	@rm -R -f docs/html

SOURCES      := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS      := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.c=%.o)))

INCLUDES     := $(call cc-includes,include)
DEPENDENCIES :=

DEFINES      := $(call cc-define,AGL_COMPILING)
DEFINES      := $(call cc-define-str,AGL_BUILD,$(BUILD))
ifeq ($(LINKAGE),static)
  DEFINES    += $(call cc-define,AGL_LINKAGE=1)
endif
ifeq ($(LINKAGE),dynamic)
  DEFINES    += $(call cc-define,AGL_LINKAGE=2)
endif

-include $(OBJECTS:%.o=%.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[CXX] $<"
	@mkdir -p ${@D}
	@$(call c++) $(INCLUDES) $(DEFINES) $(call cc-input,$<) $(call cc-output,$@)
	@$(call c++) $(INCLUDES) $(DEFINES) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(AGL): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(LINKAGE),static)
	@$(call ar++) $(call ld-output,$@) $(foreach input,$(OBJECTS),$(call ar-input,$(input)))
endif
ifeq ($(LINKAGE),dynamic)
	@$(call ld++) $(call ld-shared) $(call ld-output,$@) $(foreach input,$(OBJECTS),$(call ld-input,$(input))) $(DEPENDENCIES)
endif
