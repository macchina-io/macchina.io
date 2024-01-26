#
# Makefile
#
# Makefile for JWT Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = JWTValidator JWTBundleActivator

target      = poco.jwt
target_libs = PocoOSPWeb PocoOSP PocoJWT PocoCrypto PocoUtil PocoJSON PocoXML PocoFoundation

postbuild  = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles JWT.bndlspec

include $(POCO_BASE)/build/rules/dylib
