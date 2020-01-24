#
# Makefile
#
# Makefile for SimpleAuthService
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = SimpleAuthService

target         = com.appinf.osp.samples.auth
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SimpleAuthService.bndlspec

include $(POCO_BASE)/build/rules/dylib
