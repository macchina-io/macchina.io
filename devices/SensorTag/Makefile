#
# Makefile
#
# $Id$
#
# Makefile for macchina.io SensorTag Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/protocols/BtLE/include

objects = SensorTag SensorTagAccelerometer BundleActivator 

target         = io.macchina.btle.sensortag
target_version = 1
target_libs    = IoTBtLE IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SensorTag.bndlspec

include $(POCO_BASE)/build/rules/dylib
