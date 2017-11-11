#
# Makefile
#
# Makefile for macchina.io web console bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects =  \
	ConsoleRequestHandler \
	BundleActivator

target         = io.macchina.webui.console
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Console.bndlspec

include $(POCO_BASE)/build/rules/dylib
