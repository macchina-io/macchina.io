#
# Makefile
#
# Makefile for WebEvent sample
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = WebEventBundleActivator

target         = com.appinf.osp.samples.webevent
target_version = 1
target_libs    = PocoOSPWebEvent PocoOSPWeb PocoOSP PocoUtil PocoXML PocoNet PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebEvent.bndlspec

include $(POCO_BASE)/build/rules/dylib
