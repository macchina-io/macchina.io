#
# Makefile
#
# Makefile for macchina.io Bluetooth LE bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator \
	BlueZGATTClient

target          = io.macchina.btle.bluez
target_includes = $(PROJECT_BASE)/protocols/BtLE/include
target_libs     = IoTBtLE PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles BlueZ.bndlspec

include $(POCO_BASE)/build/rules/dylib
