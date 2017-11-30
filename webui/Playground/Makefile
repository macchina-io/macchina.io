#
# Makefile
#
# Makefile for macchina.io Playground app
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects =  \
	SandboxRequestHandler \
	Utility \
	BundleActivator

target         = io.macchina.webui.playground
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoZip PocoUtil PocoJSON PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Playground.bndlspec

include $(POCO_BASE)/build/rules/dylib
