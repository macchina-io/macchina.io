#
# Makefile
#
# Makefile for Modbus testsuite
#

include $(POCO_BASE)/build/rules/global

objects = \
	PDUWriterTest \
	PDUReaderTest \
	ModbusMasterTest \
	ModbusTestSuite \
	Driver

target          = testrunner
target_version  = 1
target_includes = $(PROJECT_BASE)/protocols/Modbus/include
target_libs     = IoTModbus PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
