#
# Makefile
#
# $Id$
#
# Makefile for macchina.io XMLDataflow sample 
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/dataflow/Engine/include
INCLUDE += -I$(PROJECT_BASE)/dataflow/XML/include

objects = XMLDataflow

target         = XMLDataflow
target_version = 1
target_libs    = IoTDataflowXML IoTDataflowEngine PocoUtil PocoJSON PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
