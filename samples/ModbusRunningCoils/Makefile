#
# Makefile
#
# Makefile for macchina.io ModbusRunningCoils sample
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator

target          = io.macchina.samples.modbusRunningCoils
target_includes = $(PROJECT_BASE)/protocols/Modbus/include $(PROJECT_BASE)/protocols/Modbus/skel/include
target_libs     = IoTModbus IoTModbusSkel PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles ModbusRunningCoils.bndlspec

include $(POCO_BASE)/build/rules/dylib
