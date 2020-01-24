#
# Makefile
#
# Makefile for SQLite Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = SQLiteBundleActivator

target      = poco.data.sqlite
target_libs = PocoOSP PocoDataSQLite PocoData PocoUtil PocoXML PocoFoundation

postbuild   = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles SQLite.bndlspec

include $(POCO_BASE)/build/rules/dylib

