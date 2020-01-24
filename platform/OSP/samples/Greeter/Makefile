#
# Makefile
#
# Makefile for Greeter
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = Greeter

target         = com.appinf.osp.samples.greeter
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Greeter.bndlspec

include $(POCO_BASE)/build/rules/dylib
