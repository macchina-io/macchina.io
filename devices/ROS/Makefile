#
# Makefile
#
# Makefile for macchina.io ROS Devices Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects =  Accelerometer Gyroscope Magnetometer GNSSSensor Sensor BundleActivator

target          = io.macchina.ros.devices
target_includes = $(PROJECT_BASE)/devices/Devices/include $(PROJECT_BASE)/protocols/ROS/include
target_libs     = IoTROS IoTDevices PocoRemotingNG PocoOSP PocoNet PocoUtil PocoXML PocoJSON PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles ROS.bndlspec

include $(POCO_BASE)/build/rules/dylib
