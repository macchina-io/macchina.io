#
# Makefile
#
# $Id$
#
# Makefile for macchina.io WebTunnel bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = BundleActivator

target         = io.macchina.protocols.webtunnel
target_version = 1
target_libs    = PocoWebTunnel PocoOSP PocoNet PocoUtil PocoXML PocoJSON PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebTunnel.bndlspec

include $(POCO_BASE)/build/rules/dylib
