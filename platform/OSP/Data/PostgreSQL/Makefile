#
# Makefile
#
# Makefile for ODBC Bundle
#

include $(POCO_BASE)/build/rules/global
include $(POCO_BASE)/OSP/BundleCreator/BundleCreator.make

objects = PostgreSQLBundleActivator

target         = poco.data.postgresql
target_version = 1
target_libs    = PocoOSP PocoDataPostgreSQL PocoData PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../../bundles PostgreSQL.bndlspec

include $(POCO_BASE)/build/rules/dylib
