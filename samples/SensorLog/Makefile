#
# Makefile
#
# Makefile for SensorLog Bundle
#

.PHONY: clean all

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

include $(POCO_BASE)/build/rules/dylib

all:
	$(shell mkdir -p ../bundles)
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SensorLog.bndlspec
	$(BUNDLE_TOOL) -o../bundles SensorLog.bndlspec



clean:
