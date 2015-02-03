#
# Makefile
#
# $Id: //poco/1.4/WebTunnel/samples-internal/WebTunnelReflector/Makefile#1 $
#
# Makefile for Reflector
#

include $(POCO_BASE)/build/rules/global

ifdef WEBTUNNEL_ENABLE_TLS
CXXFLAGS += -DWEBTUNNEL_ENABLE_TLS
tlslibs = PocoNetSSL PocoCrypto
SYSLIBS += -lssl -lcrypto -lz -ldl
endif

objects = WebTunnelReflector

target         = WebTunnelReflector
target_version = 1
target_libs    = $(tlslibs) PocoWebTunnel PocoUtil PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
