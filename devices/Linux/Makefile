#
# Makefile
#
# Makefile for macchina.io Linux Devices Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = LinuxGPIO LinuxLED BundleActivator

target          = io.macchina.linux
target_includes = $(PROJECT_BASE)/devices/Devices/include $(PROJECT_BASE)/devices/Devices/skel/include
target_libs     = IoTDevicesSkel IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Linux.bndlspec

include $(POCO_BASE)/build/rules/dylib
