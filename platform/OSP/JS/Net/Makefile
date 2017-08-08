#
# Makefile
#
# Makefile for OSP JS Net
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = NetModule

target         = com.appinf.osp.js.net
target_version = 1
target_libs    = PocoJSNet PocoJSCore PocoOSPJS PocoOSP PocoNet PocoUtil PocoXML PocoFoundation v8

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Net.bndlspec

include $(POCO_BASE)/build/rules/dylib
