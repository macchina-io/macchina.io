#
# Makefile
#
# $Id: //poco/1.4/OSP/JS/Makefile#5 $
#
# Makefile for OSP JS Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = JSExecutor JSServletExecutor \
	JSServletFilter JSServerPageFilter \
	JSSPage JSSPageReader \
	JSExtensionPoint \
	BundleWrapper ServiceRegistryWrapper ServiceRefWrapper \
	JSBundleActivator

target         = com.appinf.osp.js
target_version = 1
target_libs    = PocoJSNet PocoJSData PocoJSBridge PocoJSCore PocoOSPWeb PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoData PocoFoundation v8

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles JS.bndlspec

include $(POCO_BASE)/build/rules/dylib
