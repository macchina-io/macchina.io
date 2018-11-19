#
# BundleCreator.make
#
# Make include file for BundleCreator executable.
#
# This file defines the BUNDLE_TOOL make variable
# which can be used to invoke the BundleCreator from
# a Makefile.
#

ifndef BUNDLE_TOOL
ifneq (,$(findstring debug,$(DEFAULT_TARGET) $(MAKECMDGOALS)))
BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif
endif
