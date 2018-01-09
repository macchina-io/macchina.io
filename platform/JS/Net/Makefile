#
# Makefile
#
# Makefile for Poco JS Net library
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = HTTPRequestWrapper HTTPResponseWrapper HTMLFormWrapper

target         = PocoJSNet
target_version = 1
target_libs    = PocoJSCore PocoUtil PocoXML PocoNet PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

include $(POCO_BASE)/build/rules/lib
