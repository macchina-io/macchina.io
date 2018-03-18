#
# Makefile
#
# Makefile for macchina.io CISS Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = Sensor Accelerometer Gyroscope Magnetometer \
	NPIFrame NPIPort Node \
	BundleActivator

target          = io.macchina.ciss
target_includes = $(PROJECT_BASE)/devices/Devices/include
target_libs     = IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoSerial PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles CISS.bndlspec

include $(POCO_BASE)/build/rules/dylib
