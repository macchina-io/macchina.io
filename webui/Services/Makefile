#
# Makefile
#
# Makefile for Services Bundle
#

.PHONY: clean all

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

all:
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -o../bundles Services.bndlspec

clean:
