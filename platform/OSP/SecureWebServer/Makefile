#
# Makefile
#
# Makefile for Poco OSP SecureWebServer Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SecureWebServerBundleActivator

target      = osp.web.server.secure
target_libs = PocoOSPWeb PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SecureWebServer.bndlspec

include $(POCO_BASE)/build/rules/dylib
