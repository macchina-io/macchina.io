#
# Makefile
#
# Makefile for LogLevelCommand
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = LogLevelCommand

target         = com.appinf.osp.samples.loglevelcommand
target_version = 1
target_libs    = PocoOSPShell PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles LogLevelCommand.bndlspec

include $(POCO_BASE)/build/rules/dylib
