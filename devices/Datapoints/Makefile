#
# Makefile
#
# Makefile for IoT Datapoints 
#

.PHONY: bundle
clean all: bundle
bundle:
	$(MAKE) -f Makefile-Library $(MAKECMDGOALS)
	$(MAKE) -C skel $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Bundle $(MAKECMDGOALS)
