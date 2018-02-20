#
# Makefile
#
# Makefile for macchina.io HelloBundle sample
#

include $(POCO_BASE)/build/rules/global

include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = BundleActivator

target      = io.macchina.samples.hello
target_libs = PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles HelloBundle.bndlspec

include $(POCO_BASE)/build/rules/dylib
