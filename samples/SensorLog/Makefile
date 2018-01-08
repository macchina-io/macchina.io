#
# Makefile
#
# Makefile for SensorLog Bundle
#

.PHONY: clean all

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

all:
	$(shell mkdir -p ../bundles)
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -o../bundles SensorLog.bndlspec

clean:
