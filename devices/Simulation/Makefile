#
# Makefile
#
# Makefile for macchina.io Simulation Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

objects = SimulatedSensor SimulatedGNSSSensor BundleActivator 

target         = io.macchina.simulation
target_version = 1
target_libs    = IoTDevices PocoRemotingNG PocoOSP PocoGeo PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Simulation.bndlspec

include $(POCO_BASE)/build/rules/dylib
