#
# Makefile
#
# $Id: //poco/1.7/OSP/NetSSL_OpenSSL/Makefile#1 $
#
# Makefile for NetSSL Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = NetSSLBundleActivator

target         = poco.net.ssl
target_version = 1
target_libs    = PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles NetSSL_OpenSSL.bndlspec

include $(POCO_BASE)/build/rules/dylib
	
