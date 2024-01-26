#
# Makefile
#
# Makefile for BundleAdmin
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleAdmin BundleInstallHandler BundleListHandler \
	BundleInfoHandler RequestHandler

target         = com.appinf.osp.bundleadmin
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles BundleAdmin.bndlspec

include $(POCO_BASE)/build/rules/dylib
