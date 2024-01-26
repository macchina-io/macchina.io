#
# Makefile
#
# Makefile for TestRunner
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = TestRunnerBundleActivator

target      = com.appinf.osp.unit.testrunner
target_libs = PocoOSPUnit PocoOSP PocoXML PocoFoundation CppUnit

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles TestRunner.bndlspec

include $(POCO_BASE)/build/rules/dylib
