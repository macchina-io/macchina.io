#
# Makefile
#
# $Id: //poco/1.4/OSP/SecureWebServer/Makefile#1 $
#
# Makefile for Poco OSP SecureWebServer Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = SecureWebServerBundleActivator

target         = osp.web.server.secure
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SecureWebServer.bndlspec

include $(POCO_BASE)/build/rules/dylib
