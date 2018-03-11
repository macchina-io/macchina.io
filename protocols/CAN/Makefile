#
# Makefile
#
# Makefile for IoT CAN
#

.PHONY: bundle
clean all: bundle
bundle:
	$(MAKE) -f Makefile-Library $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Bundle $(MAKECMDGOALS)
