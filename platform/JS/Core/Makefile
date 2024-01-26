#
# Makefile
#
# Makefile for Poco JS Core library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = Wrapper PooledIsolate \
	LoggerWrapper ConsoleWrapper SystemWrapper DateTimeWrapper LocalDateTimeWrapper \
	ConfigurationWrapper ApplicationWrapper URIWrapper TimerWrapper \
	BufferWrapper UUIDWrapper JSExecutor JSTimer JSException Module ModuleRegistry

target         = PocoJSCore
target_version = 1
target_libs    = PocoUtil PocoJSON PocoXML PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
