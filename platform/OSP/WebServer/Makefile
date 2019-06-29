#
# Makefile
#
# Makefile for Poco OSP WebServer Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebServerBundleActivator

target      = osp.web.server
target_libs = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebServer.bndlspec

include $(POCO_BASE)/build/rules/dylib
