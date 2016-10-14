#
# Makefile
#
# Makefile for OSP JS Net
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = NetModule

target         = com.appinf.osp.js.net
target_version = 1
target_libs    = PocoJSNet PocoJSCore PocoOSPJS PocoOSP PocoNet PocoUtil PocoXML PocoFoundation v8

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Net.bndlspec

include $(POCO_BASE)/build/rules/dylib
