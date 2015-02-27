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
	$(MAKE) -C protocols $(MAKECMDGOALS)
	$(MAKE) -C services $(MAKECMDGOALS)
	$(MAKE) -C webui $(MAKECMDGOALS)
