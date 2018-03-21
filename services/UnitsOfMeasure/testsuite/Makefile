#
# Makefile
#
# Makefile for UnitsOfMeasure testsuite
#

include $(POCO_BASE)/build/rules/global

objects = \
	UnitsOfMeasureTest \
	UnitsOfMeasureTestSuite \
	Driver

target          = testrunner
target_version  = 1
target_includes = $(PROJECT_BASE)/services/UnitsOfMeasure/include
target_libs     = IoTUnitsOfMeasure PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
