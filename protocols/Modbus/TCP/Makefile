#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Modbus TCP bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/protocols/Modbus/include

objects = TCPPort BundleActivator

target         = io.macchina.modbus.tcp
target_version = 1
target_libs    = IoTModbus PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles TCP.bndlspec

include $(POCO_BASE)/build/rules/dylib
