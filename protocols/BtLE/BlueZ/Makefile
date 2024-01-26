#
# Makefile
#
# Makefile for macchina.io Bt LE bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator \
	HelperClient \
	BlueZGATTClient \
	BlueZPeripheralBrowser 

target          = io.macchina.btle.bluez
target_includes = $(PROJECT_BASE)/protocols/BtLE/include $(PROJECT_BASE)/protocols/BtLE/skel/include
target_libs     = IoTBtLESkel IoTBtLE PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles BlueZ.bndlspec

include $(POCO_BASE)/build/rules/dylib
