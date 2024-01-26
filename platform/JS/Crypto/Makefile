#
# Makefile
#
# Makefile for Poco JS Crypto library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = DigestEngineWrapper

target         = PocoJSCrypto
target_version = 1
target_libs    = PocoJSCore PocoCrypto PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
