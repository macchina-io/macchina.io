#
# Makefile
#
# Makefile for OSP JS Web Bundle
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = JSServletExecutor JSServletExecutorCache \
	JSServletFilter JSServerPageFilter \
	JSSPage JSSPageReader \
	SessionWrapper \
	JSWebBundleActivator

target         = com.appinf.osp.js.web
target_version = 1
target_libs    = PocoOSPJS PocoJSNet PocoJSData PocoJSBridge PocoJSCore PocoOSPWeb PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoData PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Web.bndlspec

include $(POCO_BASE)/build/rules/dylib
