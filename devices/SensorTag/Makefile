#
# Makefile
#
# $Id$
#
# Makefile for macchina.io SensorTag Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/protocols/BtLE/include

objects = SensorTag SensorTagAccelerometer BundleActivator 

target         = io.macchina.btle.sensortag
target_version = 1
target_libs    = IoTBtLE IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles SensorTag.bndlspec

include $(POCO_BASE)/build/rules/dylib
