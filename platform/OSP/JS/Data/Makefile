#
# Makefile
#
# Makefile for OSP JS Data
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = DataModule

target         = com.appinf.osp.js.data
target_version = 1
target_libs    = PocoJSData PocoJSCore PocoOSPJS PocoOSP PocoUtil PocoXML PocoData PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Data.bndlspec

include $(POCO_BASE)/build/rules/dylib
