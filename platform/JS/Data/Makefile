#
# Makefile
#
# Makefile for Poco JS Data library
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = SessionWrapper RecordSetWrapper

target         = PocoJSData
target_version = 1
target_libs    = PocoJSCore PocoData PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

include $(POCO_BASE)/build/rules/lib
