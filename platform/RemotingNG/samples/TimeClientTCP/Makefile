#
# Makefile
#
# $Id: //poco/1.6/RemotingNG/samples/TimeClientTCP/Makefile#1 $
#
# Makefile for RemotingNG TimeClient sample
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I../TimeServerTCP/include

objects = ITimeService TimeClient TimeServiceClientHelper TimeServiceEventSubscriber TimeServiceEventDispatcher \
	TimeServiceRemoteObject TimeServiceProxy TimeServiceProxyFactory

target         = TimeClient
target_version = 1
target_libs    = PocoRemotingNGTCP PocoRemotingNG PocoUtil PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
