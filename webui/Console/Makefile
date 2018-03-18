#
# Makefile
#
# Makefile for macchina.io web console bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects =  \
	ConsoleRequestHandler \
	BundleActivator

target      = io.macchina.webui.console
target_libs = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Console.bndlspec

include $(POCO_BASE)/build/rules/dylib
