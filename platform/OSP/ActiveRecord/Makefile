#
# Makefile
#
# Makefile for ActiveRecord Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = ActiveRecordBundleActivator

target      = poco.activerecord
target_libs = PocoOSP PocoUtil PocoJSON PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles ActiveRecord.bndlspec

include $(POCO_BASE)/build/rules/dylib
