#
# Makefile
#
# Makefile for OSP JS Scheduler
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = SchedulerExtensionPoint BundleActivator

target         = com.appinf.osp.js.scheduler
target_version = 1
target_libs    = PocoJSNet PocoJSData PocoJSBridge PocoJSCore PocoOSPJS PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoData PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Scheduler.bndlspec

include $(POCO_BASE)/build/rules/dylib
