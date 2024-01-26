#
# Makefile
#
# Makefile for OSP JS File
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = FileModule

target         = com.appinf.osp.js.file
target_libs    = PocoJSFile PocoJSCore PocoOSPJS PocoOSP PocoUtil PocoXML PocoData PocoFoundation
target_extlibs = v8

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles File.bndlspec

include $(POCO_BASE)/build/rules/dylib
