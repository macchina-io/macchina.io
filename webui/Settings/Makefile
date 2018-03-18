#
# Makefile
#
# Makefile for macchina.io Settings app
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects =  \
	SettingsRequestHandler \
	Utility \
	BundleActivator

target      = io.macchina.webui.settings
target_libs = PocoOSPWeb PocoOSP PocoNet PocoZip PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Settings.bndlspec

include $(POCO_BASE)/build/rules/dylib
