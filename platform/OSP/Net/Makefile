#
# Makefile
#
# Makefile for Net Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = NetBundleActivator

target      = poco.net
target_libs = PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Net.bndlspec

include $(POCO_BASE)/build/rules/dylib
