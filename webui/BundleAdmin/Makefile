#
# Makefile
#
# $Id$
#
# Makefile for macchina.io bundle administration utility
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
PAGECOMPILER = $(POCO_BASE)/PageCompiler/$(POCO_HOST_BINDIR)/cpspc

include $(POCO_BASE)/build/rules/global

objects =  \
	BundleRequestHandler \
	BundleListRequestHandler \
	BundleActionsRequestHandler \
	Utility \
	BundleActivator

target         = io.macchina.webui.bundleadmin
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoUtil PocoJSON PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles BundleAdmin.bndlspec

include $(POCO_BASE)/build/rules/dylib

# Rule for runnning PageCompiler
src/%.cpp: src/%.cpsp 
	@echo "** Compiling Page" $<
	$(SET_LD_LIBRARY_PATH) $(PAGECOMPILER) --OSP $<
