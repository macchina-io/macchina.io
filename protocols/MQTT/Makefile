#
# Makefile
#
# Makefile for IoT MQTT
#

.PHONY: bundle
clean all: bundle
bundle:
	$(MAKE) -C Paho $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Library $(MAKECMDGOALS)
	$(MAKE) -C skel $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Bundle $(MAKECMDGOALS)
