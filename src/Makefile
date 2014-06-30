#===-- src/Makefile --------------------------------------------------------===#
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

## \file src/Makefile
## \brief ...
##

#==============================================================================#

AGL_CONFIGURATION := $(CONFIGURATION)
AGL_LINKAGE       := $(LINKAGE)
AGL_CFLAGS        :=
AGL_LDFLAGS       := $(call ld-libraries,bin) $(call ld-libraries,lib)
AGL_ARFLAGS       :=

ifeq ($(AGL_LINKAGE),static)
  AGL_CFLAGS += $(call cc-define,AGL_LINKAGE=AGL_STATIC_LINKAGE)
endif
ifeq ($(AGL_LINKAGE),dynamic)
  AGL_CFLAGS += $(call cc-define,AGL_LINKAGE=AGL_DYNAMIC_LINKAGE)
endif

ifeq ($(AGL_CONFIGURATION),debug)
  AGL_CFLAGS += $(call cc-define,AGL_CONFIGURATION=AGL_CONFIGURATION_DEBUG)
  AGL_CFLAGS += $(call cc-debug)
  AGL_LDFLAGS += $(call ld-debug)
  AGL_ARFLAGS += $(call ar-debug)
endif
ifeq ($(AGL_CONFIGURATION),development)
  AGL_CFLAGS += $(call cc-define,AGL_CONFIGURATION=AGL_CONFIGURATION_DEVELOPMENT)
  AGL_CFLAGS += $(call cc-development)
  AGL_LDFLAGS += $(call ld-development)
  AGL_ARFLAGS += $(call ar-development)
endif
ifeq ($(AGL_CONFIGURATION),release)
  AGL_CFLAGS += $(call cc-define,AGL_CONFIGURATION=AGL_CONFIGURATION_RELEASE)
  AGL_CFLAGS += $(call cc-release)
  AGL_LDFLAGS += $(call ld-release)
  AGL_ARFLAGS += $(call ar-release)
endif

#===------------------------------------------------------------------------===#

ifeq ($(AGL_LINKAGE),static)
  AGL := lib/$(STATIC_LIB_PREFIX)$(PREFIX)agl$(SUFFIX)$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(AGL_LINKAGE),dynamic)
  AGL := bin/$(SHARED_LIB_PREFIX)$(PREFIX)agl$(SUFFIX)$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

AGL_INCLUDES := $(call cc-includes,include)
AGL_DEPENDENCIES :=

AGL_SOURCES := $(shell find src/agl -name '*.c')
AGL_OBJECTS := $(addprefix obj/, $(subst src/,,$(AGL_SOURCES:%.c=%.o)))
AGL_OBJECTS += obj/agl.o

AGL_DEFINES := $(call cc-define,AGL_COMPILING)

-include $(AGL_OBJECTS:%.o=%.d)

obj/agl/%.o: src/agl/%.c
	@echo "[CC] $<"
	@mkdir -p ${@D}
	@$(call c++) $(AGL_INCLUDES) $(AGL_DEFINES) $(AGL_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	@$(call c++) $(AGL_INCLUDES) $(AGL_DEFINES) $(AGL_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

obj/agl.o: src/agl.c
	@echo "[CC] $<"
	@mkdir -p ${@D}
	@$(call c++) $(AGL_INCLUDES) $(AGL_DEFINES) $(AGL_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	@$(call c++) $(AGL_INCLUDES) $(AGL_DEFINES) $(AGL_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(AGL): $(AGL_OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(AGL_LINKAGE),static)
	@$(call ar++) $(AGL_ARFLAGS) $(call ar-output,$@) $(foreach input,$(AGL_OBJECTS),$(call ar-input,$(input)))
endif
ifeq ($(AGL_LINKAGE),dynamic)
	@$(call ld++) $(call ld-shared) $(AGL_LDFLAGS) $(call ld-output,$@) $(foreach input,$(AGL_OBJECTS),$(call ld-input,$(input))) $(AGL_DEPENDENCIES)
endif

#==============================================================================#
