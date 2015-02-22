#
# Makefile
#
# $Id$
#
# Makefile for jQuery Bundle
#

.PHONY: clean all

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

all:
	$(BUNDLE_TOOL) -o../bundles jQuery.bndlspec

clean:
