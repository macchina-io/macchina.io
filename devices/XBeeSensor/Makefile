#
# Makefile
#
# $Id$
#
# Makefile for macchina.io XBee Sensor Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/protocols/XBee/include

objects = XBeeSensor BundleActivator 

target         = io.macchina.xbee.sensor
target_version = 1
target_libs    = IoTXBee IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles XBeeSensor.bndlspec

include $(POCO_BASE)/build/rules/dylib
