#
# Makefile
#
# $Id: //poco/1.4/WebTunnel/samples/WebTunnelClient/Makefile#1 $
#
# Makefile for WebTunnelClient
#

include $(POCO_BASE)/build/rules/global

ifdef WEBTUNNEL_ENABLE_TLS
CXXFLAGS += -DWEBTUNNEL_ENABLE_TLS
tlslibs = PocoNetSSL PocoCrypto
SYSLIBS += -lssl -lcrypto -lz -ldl
endif

objects = WebTunnelClient

target         = WebTunnelClient
target_version = 1
target_libs    = $(tlslibs) PocoWebTunnel PocoUtil PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
