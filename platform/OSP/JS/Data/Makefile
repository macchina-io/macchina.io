#
# Makefile
#
# Makefile for OSP JS Data
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = DataModule

target         = com.appinf.osp.js.data
target_libs    = PocoJSData PocoJSCore PocoOSPJS PocoOSP PocoUtil PocoXML PocoData PocoFoundation
target_extlibs = v8

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Data.bndlspec

include $(POCO_BASE)/build/rules/dylib
