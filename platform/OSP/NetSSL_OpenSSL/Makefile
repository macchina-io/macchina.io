#
# Makefile
#
# $Id: //poco/1.7/OSP/NetSSL_OpenSSL/Makefile#2 $
#
# Makefile for NetSSL Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = NetSSLBundleActivator

target         = poco.net.ssl
target_version = 1
target_libs    = PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles NetSSL_OpenSSL.bndlspec

include $(POCO_BASE)/build/rules/dylib
	
