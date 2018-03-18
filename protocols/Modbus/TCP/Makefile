#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Modbus TCP bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = TCPPort BundleActivator

target          = io.macchina.modbus.tcp
target_includes = $(PROJECT_BASE)/protocols/Modbus/include
target_libs     = IoTModbus PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles TCP.bndlspec

include $(POCO_BASE)/build/rules/dylib
