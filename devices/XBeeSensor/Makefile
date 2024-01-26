#
# Makefile
#
# Makefile for macchina.io XBee Sensor Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = XBeeSensor BundleActivator

target          = io.macchina.xbee.sensor
target_includes = $(PROJECT_BASE)/devices/Devices/include \
                  $(PROJECT_BASE)/devices/Devices/skel/include \
                  $(PROJECT_BASE)/protocols/XBee/include
target_libs     = IoTXBee IoTDevicesSkel IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles XBeeSensor.bndlspec

include $(POCO_BASE)/build/rules/dylib
