#
# Makefile
#
# Makefile for WebFilter sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebFilter

target         = com.appinf.osp.samples.webfilter
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebFilter.bndlspec

include $(POCO_BASE)/build/rules/dylib
