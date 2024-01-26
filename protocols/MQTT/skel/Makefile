#
# Makefile
#
# Makefile for macchina.io MQTT Skeleton
#

include $(POCO_BASE)/build/rules/global

objects := $(basename $(notdir $(wildcard src/*.cpp)))

target         = IoTMQTTSkel
target_includes = ../include
target_version = 1
target_libs    = IoTMQTT PocoRemotingNG PocoOSP PocoFoundation

include $(POCO_BASE)/build/rules/lib
