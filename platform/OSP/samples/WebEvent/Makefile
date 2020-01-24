#
# Makefile
#
# Makefile for WebEvent sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebEventBundleActivator

target         = com.appinf.osp.samples.webevent
target_libs    = PocoOSPWebEvent PocoOSPWeb PocoOSP PocoUtil PocoXML PocoNet PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebEvent.bndlspec

include $(POCO_BASE)/build/rules/dylib
