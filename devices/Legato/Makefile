#
# Makefile
#
# Makefile for IoT Legato Library
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = GNSSSensorImpl VoltageSensorImpl BundleActivator

target          = io.macchina.legato
target_includes = $(PROJECT_BASE)/devices/Devices/include \
                  $(PROJECT_BASE)/devices/Devices/skel/include \
                  $(PROJECT_BASE)/devices/GNSS/NMEA/include
target_libs     = IoTGNSSNMEA IoTDevicesSkel IoTDevices PocoGeo PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Legato.bndlspec

include $(POCO_BASE)/build/rules/dylib
