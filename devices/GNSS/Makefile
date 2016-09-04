#
# Makefile
#
# $Id$
#
# Makefile for IoT GNSS Library
#

include $(POCO_BASE)/build/rules/global

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/devices/GNSS/NMEA/include
INCLUDE += -I$(PROJECT_BASE)/devices/Serial/include

objects = GNSSSensorImpl BundleActivator

target         = io.macchina.gnss.nmea
target_version = 1
target_libs    = IoTGNSSNMEA IoTDevices PocoSerial PocoGeo PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles GNSS.bndlspec

include $(POCO_BASE)/build/rules/dylib
