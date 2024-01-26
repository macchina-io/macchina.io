#
# Makefile
#
# Makefile for macchina.io Modbus TCP
#

.PHONY: bundle
clean all: bundle
bundle:
	$(MAKE) -f Makefile-Library $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Bundle $(MAKECMDGOALS)
