#
# Makefile
#
# $Id: //poco/1.4/OSP/Data/SQLite/Makefile#2 $
#
# Makefile for SQLite Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

objects = SQLiteBundleActivator

target         = poco.data.sqlite
target_version = 1
target_libs    = PocoOSP PocoDataSQLite PocoData PocoUtil PocoXML PocoFoundation

postbuild      = $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles SQLite.bndlspec

include $(POCO_BASE)/build/rules/dylib
