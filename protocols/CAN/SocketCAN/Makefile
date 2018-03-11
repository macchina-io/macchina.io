#
# Makefile
#
# $Id$
#
# Makefile for macchina.io SocketCAN bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

INCLUDE += -I$(PROJECT_BASE)/protocols/CAN/include

ifeq ($(OSNAME),Linux)
CXXFLAGS += -DMACCHINA_HAVE_SOCKETCAN
endif

objects = CANSocket CANEndpointImpl BundleActivator

target         = io.macchina.can.socketcan
target_version = 1
target_libs    = IoTCAN PocoOSP PocoRemotingNG PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles SocketCAN.bndlspec

include $(POCO_BASE)/build/rules/dylib
