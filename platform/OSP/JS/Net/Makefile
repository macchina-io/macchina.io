#
# Makefile
#
# Makefile for OSP JS Net
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = NetModule

target         = com.appinf.osp.js.net
target_version = 1
target_libs    = PocoJSNet PocoJSCore PocoOSPJS PocoOSP PocoNet PocoUtil PocoXML PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Net.bndlspec

include $(POCO_BASE)/build/rules/dylib
