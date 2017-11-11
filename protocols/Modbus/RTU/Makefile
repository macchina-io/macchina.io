#
# Makefile
#
# Makefile for macchina.io Modbus bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/protocols/Modbus/include
INCLUDE += -I$(PROJECT_BASE)/devices/Serial/include

objects = RTUPort BundleActivator

target         = io.macchina.modbus.rtu
target_version = 1
target_libs    = IoTModbus PocoSerial PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles RTU.bndlspec

include $(POCO_BASE)/build/rules/dylib
