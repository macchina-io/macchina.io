#
# Makefile
#
# $Id: //poco/1.7/OSP/Core/Makefile#2 $
#
# Makefile for Core Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = CoreBundleActivator

target         = osp.core
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Core.bndlspec

include $(POCO_BASE)/build/rules/dylib
