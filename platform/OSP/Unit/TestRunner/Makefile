#
# Makefile
#
# $Id: //projects/SecurePassage/FireMon/poco/OSP/Unit/TestRunner/Makefile#1 $
#
# Makefile for TestRunner
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = TestRunnerBundleActivator

target         = com.appinf.osp.unit.testrunner
target_version = 1
target_libs    = PocoOSPUnit PocoOSP PocoXML PocoFoundation CppUnit

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles TestRunner.bndlspec

include $(POCO_BASE)/build/rules/dylib
