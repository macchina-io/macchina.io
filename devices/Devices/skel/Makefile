#
# Makefile
#
# Makefile for macchina.io Devices Skeleton
#

include $(POCO_BASE)/build/rules/global

objects := $(basename $(notdir $(wildcard src/*.cpp)))

target         = IoTDevicesSkel
target_includes = ../include
target_version = 1
target_libs    = IoTDevices PocoRemotingNG PocoOSP PocoFoundation

include $(POCO_BASE)/build/rules/lib
