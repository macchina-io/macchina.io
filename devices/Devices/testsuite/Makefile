#
# Makefile
#
# $Id$
#
# Makefile for IoT Devices testsuite
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

objects = \
	EventModerationPolicyTest \
	DevicesTestSuite \
	Driver

target         = testrunner
target_version = 1
target_libs    = IoTDevices PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
