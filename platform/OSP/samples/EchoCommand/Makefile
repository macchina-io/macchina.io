#
# Makefile
#
# Makefile for EchoCommand
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = EchoCommand

target         = com.appinf.osp.samples.echocommand
target_version = 1
target_libs    = PocoOSPShell PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles EchoCommand.bndlspec

include $(POCO_BASE)/build/rules/dylib
