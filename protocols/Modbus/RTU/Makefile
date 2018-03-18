#
# Makefile
#
# Makefile for macchina.io Modbus bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = RTUPort BundleActivator

target          = io.macchina.modbus.rtu
target_includes = $(PROJECT_BASE)/protocols/Modbus/include \
                  $(PROJECT_BASE)/devices/Serial/include
target_libs     = IoTModbus PocoSerial PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles RTU.bndlspec

include $(POCO_BASE)/build/rules/dylib
