#
# Makefile
#
# Makefile for macchina.io Legato MobileConnectionService bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = MobileConnectionServiceImpl BundleActivator

target          = io.macchina.services.mobileconnection.legato
target_includes = $(PROJECT_BASE)/services/MobileConnection/include
target_libs     = IoTMobileConnection PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles Legato.bndlspec

include $(POCO_BASE)/build/rules/dylib
