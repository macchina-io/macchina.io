#
# Makefile
#
# $Id$
#
# Makefile for macchina.io web application launcher bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
    PAGECOMPILER = $(POCO_BASE)/PageCompiler/$(POCO_HOST_BINDIR)/cpspcd
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
    PAGECOMPILER = $(POCO_BASE)/PageCompiler/$(POCO_HOST_BINDIR)/cpspc
endif

objects =  \
	LoginPage \
	ControllerRequestHandler \
	SessionJSON \
	Utility \
	AppRegistry \
	AppExtensionPoint \
	LauncherAppsJSON \
	BundleActivator

target         = io.macchina.webui.launcher
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Launcher.bndlspec

include $(POCO_BASE)/build/rules/dylib

# Rule for runnning PageCompiler
src/%.cpp: src/%.cpsp 
	@echo "** Compiling Page" $<
	$(SET_LD_LIBRARY_PATH) $(PAGECOMPILER) --OSP $<
