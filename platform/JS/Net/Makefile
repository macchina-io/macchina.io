#
# Makefile
#
# Makefile for Poco JS Net library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = HTTPRequestWrapper HTTPResponseWrapper HTMLFormWrapper CookieJar CookieJarWrapper

target         = PocoJSNet
target_version = 1
target_libs    = PocoJSCore PocoUtil PocoXML PocoNet PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
