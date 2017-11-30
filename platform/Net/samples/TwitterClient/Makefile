#
# Makefile
#
# Makefile for Poco Twitter Client
#

include $(POCO_BASE)/build/rules/global

objects = Twitter TweetApp

target         = tweet
target_version = 1
target_libs    = PocoUtil PocoJSON PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec

ifdef POCO_UNBUNDLED
        SYSLIBS += -lz -lpcre -lexpat
endif
