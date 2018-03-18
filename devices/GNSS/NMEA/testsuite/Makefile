#
# Makefile
#
# Makefile for IoT GNSS NMEA testsuite
#

include $(POCO_BASE)/build/rules/global

objects = NMEATestSuite Driver \
	SentenceDecoderTest RMCProcessorTest GGAProcessorTest

target          = testrunner
target_version  = 1
target_includes = $(PROJECT_BASE)/devices/GNSS/NMEA/include
target_libs     = IoTGNSSNMEA PocoGeo PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
