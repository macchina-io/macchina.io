#
# Makefile
#
# $Id$
#
# Makefile for DataFlow testsuite
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/dataflow/engine/include

objects = \
ArithmeticNodesTest \
ComputationNodesTest \
FlowNodesTest \
LogicalNodesTest \
RelationalNodesTest \
TimingNodesTest \
DataFlowMasterTest \
DataFlowTestSuite \
Driver

target         = testrunner
target_version = 1
target_libs    = IoTDataflowEngine PocoUtil PocoXML PocoJSON PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
