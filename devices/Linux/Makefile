#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Linux Devices Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

objects = LinuxGPIO LinuxLED BundleActivator

target         = io.macchina.linux
target_version = 1
target_libs    = IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Linux.bndlspec

include $(POCO_BASE)/build/rules/dylib
