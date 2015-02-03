#
# Makefile
#
# $Id$
#
# Global Makefile for macchina.io
#

.PHONY: clean all

clean all:
	$(MAKE) -C platform $(MAKECMDGOALS)
	$(MAKE) -C server $(MAKECMDGOALS)
	$(MAKE) -C devices $(MAKECMDGOALS)
