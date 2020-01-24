#
# Makefile
#
# Makefile for NetSSL Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = NetSSLBundleActivator

target      = poco.net.ssl
target_libs = PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild  = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles NetSSL_OpenSSL.bndlspec

include $(POCO_BASE)/build/rules/dylib
