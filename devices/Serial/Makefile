#
# Makefile
#
# Makefile for macchina.io Serial bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SerialDeviceImpl BundleActivator

target          = io.macchina.serial
target_includes = $(PROJECT_BASE)/devices/Devices/include $(PROJECT_BASE)/devices/Devices/skel/include
target_libs     = IoTDevicesSkel IoTDevices PocoSerial PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Serial.bndlspec

include $(POCO_BASE)/build/rules/dylib
