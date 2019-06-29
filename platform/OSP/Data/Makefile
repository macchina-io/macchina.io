#
# Makefile
#
# Makefile for Data Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = DataBundleActivator

target      = poco.data
target_libs = PocoOSP PocoData PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Data.bndlspec

include $(POCO_BASE)/build/rules/dylib

