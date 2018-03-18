#
# Makefile
#
# Makefile for macchina.io XDK Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = XDKSensor HighRateSensor HighRateAccelerometer HighRateGyroscope HighRateMagnetometer HighRateButton BundleActivator

target          = io.macchina.xdk
target_includes = $(PROJECT_BASE)/devices/Devices/include \
                  $(PROJECT_BASE)/protocols/BtLE/include
target_libs     = IoTBtLE IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles XDK.bndlspec

include $(POCO_BASE)/build/rules/dylib
