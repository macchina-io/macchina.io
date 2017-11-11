#
# Makefile
#
# Makefile for ServiceListener
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = ServiceListener

target         = com.appinf.osp.samples.servicelistener
target_version = 1
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles ServiceListener.bndlspec

include $(POCO_BASE)/build/rules/dylib
