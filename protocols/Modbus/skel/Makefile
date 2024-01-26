#
# Makefile
#
# Makefile for macchina.io Modbus Skeleton
#

include $(POCO_BASE)/build/rules/global

objects := $(basename $(notdir $(wildcard src/*.cpp)))

target         = IoTModbusSkel
target_includes = ../include
target_version = 1
target_libs    = IoTModbus PocoRemotingNG PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

include $(POCO_BASE)/build/rules/lib
