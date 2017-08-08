#
# Makefile
#
# $Id$
#
# Makefile for OSP JS Web Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = JSServletExecutor JSServletExecutorCache \
	JSServletFilter JSServerPageFilter \
	JSSPage JSSPageReader \
	SessionWrapper \
	JSWebBundleActivator

target         = com.appinf.osp.js.web
target_version = 1
target_libs    = PocoOSPJS PocoJSNet PocoJSData PocoJSBridge PocoJSCore PocoOSPWeb PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoData PocoFoundation v8

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Web.bndlspec

include $(POCO_BASE)/build/rules/dylib
