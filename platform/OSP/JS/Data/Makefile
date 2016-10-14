#
# Makefile
#
# Makefile for OSP JS Data
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = DataModule

target         = com.appinf.osp.js.data
target_version = 1
target_libs    = PocoJSData PocoJSCore PocoOSPJS PocoOSP PocoUtil PocoXML PocoData PocoFoundation v8

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Data.bndlspec

include $(POCO_BASE)/build/rules/dylib
