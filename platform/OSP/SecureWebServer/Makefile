#
# Makefile
#
# $Id: //poco/1.7/OSP/SecureWebServer/Makefile#2 $
#
# Makefile for Poco OSP SecureWebServer Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = SecureWebServerBundleActivator

target         = osp.web.server.secure
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SecureWebServer.bndlspec

include $(POCO_BASE)/build/rules/dylib
