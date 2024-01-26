#
# Makefile
#
# Makefile for macchina.io SensorTag Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SensorTag SensorTagAccelerometer BundleActivator

target          = io.macchina.sensortag
target_includes = $(PROJECT_BASE)/devices/Devices/include \
                  $(PROJECT_BASE)/devices/Devices/skel/include \
                  $(PROJECT_BASE)/protocols/BtLE/include
target_libs     = IoTBtLE IoTDevicesSkel IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SensorTag.bndlspec

include $(POCO_BASE)/build/rules/dylib
