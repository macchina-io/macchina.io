#
# Makefile
#
# Makefile for MomentJS Bundle
#

.PHONY: clean all

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

all:
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -o../bundles MomentJS.bndlspec

clean:
