#
# Makefile
#
# $Id$
#
# Makefile for TinyColor Bundle
#

.PHONY: clean all

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

all:
	$(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -o../bundles TinyColor.bndlspec

clean:
