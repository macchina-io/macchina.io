#
# Makefile
#
# Makefile for WebIndex sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebIndex

target         = com.appinf.osp.samples.webindex
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebIndex.bndlspec

include $(POCO_BASE)/build/rules/dylib
