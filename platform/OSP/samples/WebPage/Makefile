#
# Makefile
#
# $Id: //poco/1.7/OSP/samples/WebPage/Makefile#2 $
#
# Makefile for WebPage
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = WebPage

target         = com.appinf.osp.samples.webpage
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles WebPage.bndlspec

include $(POCO_BASE)/build/rules/dylib
