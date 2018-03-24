#
# Makefile
#
# Makefile for CANDevices testsuite
#

include $(POCO_BASE)/build/rules/global

objects = \
	BitStreamTest \
	CANDevicesTestSuite \
	Driver

target          = testrunner
target_version  = 1
target_includes = $(PROJECT_BASE)/devices/CAN/include
target_libs     = IoTCANDevices IoTCAN IoTDevices PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
