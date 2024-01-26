#
# Makefile
#
# Makefile for Poco JS File library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = FileWrapper FileStreamWrapper

target         = PocoJSFile
target_version = 1
target_libs    = PocoJSCore PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
