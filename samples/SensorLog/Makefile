#
# Makefile
#
# Makefile for SensorLog Bundle
#

.PHONY: clean all

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

include $(POCO_BASE)/build/rules/global

all:
	$(BUNDLE_TOOL) -o../bundles SensorLog.bndlspec

clean:
