#
# Makefile
#
# $Id: //poco/1.7/OSP/samples/WebEvent/Makefile#2 $
#
# Makefile for WebEvent sample
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = WebEventBundleActivator

target         = com.appinf.osp.samples.webevent
target_version = 1
target_libs    = PocoOSPWebEvent PocoOSPWeb PocoOSP PocoUtil PocoXML PocoNet PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebEvent.bndlspec

include $(POCO_BASE)/build/rules/dylib
