#
# Makefile
#
# $Id: //poco/1.6/RemotingNG/TCP/Makefile#1 $
#
# Makefile for Poco RemotingNG TCP Transport
#

include $(POCO_BASE)/build/rules/global

objects = \
	ChannelStream \
	Connection \
	ConnectionManager \
	Frame \
	FrameQueue \
	Listener \
	ServerConnection \
	ServerConnectionFactory \
	ServerTransport \
	SocketFactory \
	Timer \
	Transport \
	TransportFactory

target         = PocoRemotingNGTCP
target_version = $(LIBVERSION)
target_libs    = PocoRemotingNG PocoNet PocoFoundation $(POCO_LICENSING)

include $(POCO_BASE)/build/rules/lib
