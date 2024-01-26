#
# Makefile
#
# Makefile for TestBundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = TestBundleActivator BundleTest TestBundleSuite

target      = com.appinf.osp.unit.sample
target_libs = PocoOSPUnit PocoOSP PocoUtil PocoXML PocoFoundation CppUnit

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../../samples/bundles TestBundle.bndlspec

include $(POCO_BASE)/build/rules/dylib
