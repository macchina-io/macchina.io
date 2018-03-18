#
# Makefile
#
# Makefile for OSP RemotingNG TCP bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator

target      = com.appinf.osp.remotingng.tcp
target_libs = PocoRemotingNGTCP PocoRemotingNG PocoOSP PocoNet PocoUtil PocoXML PocoJSON PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles TCP.bndlspec

include $(POCO_BASE)/build/rules/dylib
