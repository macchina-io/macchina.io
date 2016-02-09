#
# Makefile
#
# $Id: //poco/1.4/JS/Core/Makefile#7 $
#
# Makefile for Poco JS Core library
#

include $(POCO_BASE)/build/rules/global

V8VERSION = 0x031C0400 

CXXFLAGS += -DPOCO_JS_V8VERSION=$(V8VERSION)

objects = Wrapper PooledIsolate \
	LoggerWrapper ConsoleWrapper SystemWrapper DateTimeWrapper LocalDateTimeWrapper \
	ConfigurationWrapper ApplicationWrapper URIWrapper TimerWrapper \
	BufferWrapper JSExecutor JSException

target         = PocoJSCore
target_version = 1
target_libs    = PocoUtil PocoXML PocoFoundation v8

include $(POCO_BASE)/build/rules/lib
