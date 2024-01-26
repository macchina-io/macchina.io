#
# Makefile
#
# Makefile for macchina.io Datapoints Skeleton
#

include $(POCO_BASE)/build/rules/global

objects := $(basename $(notdir $(wildcard src/*.cpp)))

target          = IoTDatapointsSkel
target_includes = ../include ../../Devices/include ../../Devices/skel/include
target_version  = 1
target_libs     = IoTDatapoints IoTDevices PocoRemotingNG PocoOSP PocoFoundation

include $(POCO_BASE)/build/rules/lib
