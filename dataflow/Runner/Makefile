#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Dataflow Runner
#

.PHONY: bundle
clean all: bundle
bundle:
	$(MAKE) -f Makefile-Library $(MAKECMDGOALS)
	$(MAKE) -f Makefile-Bundle $(MAKECMDGOALS)
