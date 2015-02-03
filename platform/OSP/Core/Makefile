#
# Makefile
#
# $Id: //poco/1.4/OSP/Core/Makefile#1 $
#
# Makefile for Core Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = CoreBundleActivator

target         = osp.core
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Core.bndlspec

include $(POCO_BASE)/build/rules/dylib
