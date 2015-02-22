#
# Makefile
#
# $Id$
#
# Makefile for AngularJS Bundle
#

.PHONY: clean all

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

all:
	$(BUNDLE_TOOL) -o../bundles AngularJS.bndlspec

clean:
