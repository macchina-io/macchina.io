#
# Makefile
#
# $Id: //poco/1.7/OSP/samples/Extension/Makefile#2 $
#
# Makefile for Extension
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = Extension

target         = com.appinf.osp.samples.extension
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Extension.bndlspec

include $(POCO_BASE)/build/rules/dylib
