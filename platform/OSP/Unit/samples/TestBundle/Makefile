#
# Makefile
#
# Makefile for TestBundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = TestBundleActivator BundleTest TestBundleSuite

target         = com.appinf.osp.unit.sample
target_version = 1
target_libs    = PocoOSPUnit PocoOSP PocoUtil PocoXML PocoFoundation CppUnit

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../../samples/bundles TestBundle.bndlspec

include $(POCO_BASE)/build/rules/dylib
