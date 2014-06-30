#===-- Makefile ------------------------------------------------------------===#
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

-include config.mk
ifndef _AGL_BUILD_CONFIG_
  $(error Please ./configure first.)
endif

include mk/detect/platform.mk
include mk/detect/architecture.mk
include mk/toolchain.mk
include mk/platform.mk
include mk/architecture.mk

.PHONY: all docs clean agl

all: agl

include src/Makefile

agl: $(AGL)

docs:
	@echo "[DOXYGEN] Doxyfile"
	@doxygen Doxyfile

clean:
	@echo "Cleaning..."
	@rm -R -f obj
	@rm -R -f docs
	@rm -f lib/$(PREFIX)agl$(SUFFIX).lib
	@rm -f lib/$(PREFIX)agl$(SUFFIX).pdb
