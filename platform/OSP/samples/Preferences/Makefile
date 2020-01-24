#
# Makefile
#
# Makefile for Preferences
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = Preferences

target         = com.appinf.osp.samples.preferences
target_libs    = PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Preferences.bndlspec

include $(POCO_BASE)/build/rules/dylib
