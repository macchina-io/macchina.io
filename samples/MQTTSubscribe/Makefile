#
# Makefile
#
# Makefile for macchina.io MQTTSubscribe sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator

target          = io.macchina.samples.mqttsubscribe
target_includes = $(PROJECT_BASE)/protocols/MQTT/include $(PROJECT_BASE)/protocols/MQTT/skel/include
target_libs     = IoTMQTT IoTMQTTSkel PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles MQTTSubscribe.bndlspec

include $(POCO_BASE)/build/rules/dylib
