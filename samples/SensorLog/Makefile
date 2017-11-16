#
# Makefile
#
# Makefile for SensorLog Bundle
#

.PHONY: clean all

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

include $(POCO_BASE)/build/rules/dylib

all:
	$(shell mkdir -p ../bundles)
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SensorLog.bndlspec
	$(BUNDLE_TOOL) -o../bundles SensorLog.bndlspec



clean:
