#
# Makefile
#
# $Id: //poco/1.7/OSP/Data/SQLite/Makefile#2 $
#
# Makefile for SQLite Bundle
#

include $(POCO_BASE)/build/rules/global

ifneq (,$(findstring debug,$(DEFAULT_TARGET)))
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundled
else
	BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
endif

objects = SQLiteBundleActivator

target         = poco.data.sqlite
target_version = 1
target_libs    = PocoOSP PocoDataSQLite PocoData PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles SQLite.bndlspec

include $(POCO_BASE)/build/rules/dylib
