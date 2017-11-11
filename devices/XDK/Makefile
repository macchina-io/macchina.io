#
# Makefile
#
# Makefile for macchina.io XDK Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include
INCLUDE += -I$(PROJECT_BASE)/protocols/BtLE/include

objects = XDKSensor HighRateSensor HighRateAccelerometer HighRateGyroscope HighRateMagnetometer HighRateButton BundleActivator 

target         = io.macchina.btle.xdk
target_version = 1
target_libs    = IoTBtLE IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles XDK.bndlspec

include $(POCO_BASE)/build/rules/dylib
