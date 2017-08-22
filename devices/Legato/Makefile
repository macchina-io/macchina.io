#
# Makefile
#
# $Id$
#
# Makefile for IoT Legato Library
#

include $(POCO_BASE)/build/rules/global

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/devices/GNSS/NMEA/include

objects = GNSSSensorImpl BundleActivator

target         = io.macchina.legato
target_version = 1
target_libs    = IoTGNSSNMEA IoTDevices PocoGeo PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Legato.bndlspec

include $(POCO_BASE)/build/rules/dylib
