#
# Makefile
#
# Makefile for WebPage
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebPage

target         = com.appinf.osp.samples.webpage
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebPage.bndlspec

include $(POCO_BASE)/build/rules/dylib
