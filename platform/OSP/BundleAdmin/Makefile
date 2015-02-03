#
# Makefile
#
# $Id: //poco/1.4/OSP/BundleAdmin/Makefile#1 $
#
# Makefile for BundleAdmin
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = BundleAdmin BundleInstallHandler BundleListHandler \
	BundleInfoHandler RequestHandler

target         = com.appinf.osp.bundleadmin
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles BundleAdmin.bndlspec

include $(POCO_BASE)/build/rules/dylib
