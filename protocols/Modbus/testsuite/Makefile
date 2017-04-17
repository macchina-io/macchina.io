#
# Makefile
#
# $Id$
#
# Makefile for Modbus testsuite
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/protocols/Modbus/include

objects = \
	PDUWriterTest \
	PDUReaderTest \
	ModbusMasterTest \
	ModbusTestSuite \
	Driver

target         = testrunner
target_version = 1
target_libs    = IoTModbus PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
