#
# Makefile
#
# $Id: //poco/1.7/RemotingNG/TCP/testsuite/Makefile#1 $
#
# Makefile for Poco RemotingNG TCP Transport testsuite
#

include $(POCO_BASE)/build/rules/global

objects = \
	Driver \
	RemotingTest \
	TCPTestSuite \
	Tester \
	ITester \
	TesterClientHelper \
	TesterEventDispatcher \
	TesterEventSubscriber \
	TesterProxy \
	TesterProxyFactory \
	TesterRemoteObject \
	TesterServerHelper \
	TesterSkeleton

target         = testrunner
target_version = 1
target_libs    = PocoRemotingNGTCP PocoRemotingNG PocoNet PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
