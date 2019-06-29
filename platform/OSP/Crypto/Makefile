#
# Makefile
#
# Makefile for Crypto Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = CryptoBundleActivator

target      = poco.crypto
target_libs = PocoCrypto PocoOSP PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Crypto.bndlspec

include $(POCO_BASE)/build/rules/dylib

