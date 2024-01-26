#
# Makefile
#
# Makefile for OSP RemotingNG REST bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator

target      = com.appinf.osp.remotingng.rest
target_libs = PocoRemotingNGREST PocoRemotingNG PocoOSP PocoNetSSL PocoNet PocoUtil PocoXML PocoJSON PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles REST.bndlspec

include $(POCO_BASE)/build/rules/dylib
