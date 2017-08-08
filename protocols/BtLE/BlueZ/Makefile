#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Bluetooth LE bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

INCLUDE += -I$(PROJECT_BASE)/protocols/BtLE/include

objects = BundleActivator \
	BlueZGATTClient

target         = io.macchina.btle.bluez
target_version = 1
target_libs    = IoTBtLE PocoOSP PocoRemotingNG PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles BlueZ.bndlspec

include $(POCO_BASE)/build/rules/dylib
