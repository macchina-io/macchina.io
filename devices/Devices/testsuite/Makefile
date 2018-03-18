#
# Makefile
#
# Makefile for IoT Devices testsuite
#

include $(POCO_BASE)/build/rules/global

objects = \
	EventModerationPolicyTest \
	DevicesTestSuite \
	Driver

target          = testrunner
target_version  = 1
target_includes = $(PROJECT_BASE)/devices/Devices/include
target_libs     = IoTDevices PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
