#
# Makefile
#
# Makefile for OSP SimpleAuth
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SimpleAuth

target      = com.appinf.osp.simple-auth
target_libs = PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SimpleAuth.bndlspec

include $(POCO_BASE)/build/rules/dylib
