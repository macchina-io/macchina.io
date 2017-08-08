#
# Makefile
#
# $Id$
#
# Makefile for OSP SimpleAuth
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = SimpleAuth

target         = com.appinf.osp.simple-auth
target_version = 1
target_libs    = PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SimpleAuth.bndlspec

include $(POCO_BASE)/build/rules/dylib
