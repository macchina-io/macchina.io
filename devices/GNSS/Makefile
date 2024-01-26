#
# Makefile
#
# Makefile for IoT GNSS Library
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = GNSSSensorImpl BundleActivator

target          = io.macchina.gnss.nmea
target_includes = $(PROJECT_BASE)/devices/Devices/include \
target_includes = $(PROJECT_BASE)/devices/Devices/skel/include \
                  $(PROJECT_BASE)/devices/GNSS/NMEA/include \
                  $(PROJECT_BASE)/devices/Serial/include
target_libs     = IoTGNSSNMEA IoTDevicesSkel IoTDevices PocoSerial PocoGeo PocoOSP PocoUtil PocoXML PocoJSON PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles GNSS.bndlspec

include $(POCO_BASE)/build/rules/dylib
