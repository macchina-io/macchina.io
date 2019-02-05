#
# Makefile
#
# Makefile for macchina.io web application launcher bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make
include $(POCO_BASE)/PageCompiler/PageCompiler.make

objects =  \
	LoginPage \
	ControllerRequestHandler \
	SessionJSON \
	Utility \
	AppRegistry \
	AppExtensionPoint \
	LauncherAppsJSON \
	BundleActivator

target      = io.macchina.webui.launcher
target_libs = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Launcher.bndlspec

include $(POCO_BASE)/build/rules/dylib

# Rule for runnning PageCompiler
src/%.cpp: src/%.cpsp
	@echo "** Compiling Page" $<
	-$(SET_LD_LIBRARY_PATH) $(PAGE_COMPILER) --OSP $<
