#
# Makefile
#
# Makefile for Poco JS Data library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = SessionWrapper RecordSetWrapper

target         = PocoJSData
target_version = 1
target_libs    = PocoJSCore PocoData PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
