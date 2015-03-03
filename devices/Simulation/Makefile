#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Simulation Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

objects = SimulatedSensor BundleActivator 

target         = io.macchina.simulation
target_version = 1
target_libs    = IoTDevices PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Simulation.bndlspec

include $(POCO_BASE)/build/rules/dylib
