#
# Makefile
#
# Makefile for macchina.io Simple Linux Thermal Sensor Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = LinuxThermalSensor BundleActivator

target          = io.macchina.linux-thermal-simple
target_includes = $(PROJECT_BASE)/devices/Devices/include
target_libs     = IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles LinuxThermalSimple.bndlspec

include $(POCO_BASE)/build/rules/dylib
