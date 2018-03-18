#
# Makefile
#
# Makefile for macchina.io Sensor2MQTT sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator MQTTTask

target          = io.macchina.samples.sensor2mqtt
target_includes = $(PROJECT_BASE)/devices/Devices/include \
                  $(PROJECT_BASE)/protocols/MQTT/include
target_libs     = IoTDevices IoTMQTT PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Sensor2MQTT.bndlspec

include $(POCO_BASE)/build/rules/dylib
