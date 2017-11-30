#
# Makefile
#
# Makefile for IoT Legato Library
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/devices/GNSS/NMEA/include

objects = GNSSSensorImpl VoltageSensorImpl BundleActivator

target         = io.macchina.legato
target_version = 1
target_libs    = IoTGNSSNMEA IoTDevices PocoGeo PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Legato.bndlspec

include $(POCO_BASE)/build/rules/dylib
