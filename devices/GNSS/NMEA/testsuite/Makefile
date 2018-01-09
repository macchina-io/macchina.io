#
# Makefile
#
# Makefile for IoT GNSS NMEA testsuite
#

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/GNSS/NMEA/include

objects = NMEATestSuite Driver \
	SentenceDecoderTest RMCProcessorTest GGAProcessorTest

target         = testrunner
target_version = 1
target_libs    = IoTGNSSNMEA PocoGeo PocoFoundation CppUnit

include $(POCO_BASE)/build/rules/exec
