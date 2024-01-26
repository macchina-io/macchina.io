#
# Makefile
#
# Makefile for macchina.io Simulation Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SimulatedSensor SimulatedGNSSSensor BundleActivator

target          = io.macchina.simulation
target_includes = $(PROJECT_BASE)/devices/Devices/include $(PROJECT_BASE)/devices/Devices/skel/include
target_libs     = IoTDevicesSkel IoTDevices PocoRemotingNG PocoOSP PocoGeo PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Simulation.bndlspec

include $(POCO_BASE)/build/rules/dylib
