#
# Makefile
#
# Makefile for Extensible
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = Extensible

target         = com.appinf.osp.samples.extensible
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Extensible.bndlspec

include $(POCO_BASE)/build/rules/dylib
