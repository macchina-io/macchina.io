#
# Makefile
#
# Makefile for OSP JS Crypto
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = CryptoModule

target         = com.appinf.osp.js.crypto
target_libs    = PocoJSCrypto PocoJSCore PocoOSPJS PocoOSP PocoCrypto PocoUtil PocoXML PocoData PocoFoundation
target_extlibs = v8

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Crypto.bndlspec

include $(POCO_BASE)/build/rules/dylib
