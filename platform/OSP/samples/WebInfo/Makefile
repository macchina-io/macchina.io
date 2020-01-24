#
# Makefile
#
# Makefile for WebInfo sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebInfo

target         = com.appinf.osp.samples.webinfo
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebInfo.bndlspec

include $(POCO_BASE)/build/rules/dylib
