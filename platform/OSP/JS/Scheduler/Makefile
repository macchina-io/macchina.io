#
# Makefile
#
# Makefile for OSP JS Scheduler
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = SchedulerExtensionPoint BundleActivator

target         = com.appinf.osp.js.scheduler
target_version = 1
target_libs    = PocoJSNet PocoJSData PocoJSBridge PocoJSCore PocoOSPJS PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoData PocoFoundation v8

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Scheduler.bndlspec

include $(POCO_BASE)/build/rules/dylib
