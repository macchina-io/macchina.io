#
# Makefile
#
# $Id: //poco/1.6/OSP/Crypto/Makefile#1 $
#
# Makefile for Crypto Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = CryptoBundleActivator

target         = poco.crypto
target_version = 1
target_libs    = PocoCrypto PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Crypto.bndlspec

include $(POCO_BASE)/build/rules/dylib
	
