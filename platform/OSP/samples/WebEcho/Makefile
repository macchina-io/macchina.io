#
# Makefile
#
# Makefile for WebEcho sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = WebEcho

target         = com.appinf.osp.samples.webecho
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebEcho.bndlspec

include $(POCO_BASE)/build/rules/dylib
