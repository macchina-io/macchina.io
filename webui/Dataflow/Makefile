#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Dataflow bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects =  \
	DataflowRequestHandler \
	Utility \
	BundleActivator

target         = io.macchina.webui.dataflow
target_version = 1
target_libs    = PocoOSPWeb PocoOSP PocoNet PocoZip PocoUtil PocoJSON PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Dataflow.bndlspec

include $(POCO_BASE)/build/rules/dylib
