#
# Makefile
#
# $Id$
#
# Makefile for Poco OPC testsuite
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/protocols/OPC/include

objects = Driver OPCTest OPCTestSuite

target         = testrunner
target_version = 1
target_libs    = IoTOPC PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
