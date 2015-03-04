#
# Makefile
#
# $Id$
#
# Global Makefile for macchina.io
#

.PHONY: clean all install_sdk install_runtime install

TARGET ?= sdk
INSTALLDIR ?= /usr/local/macchina

MACCHINA_BASE = $(shell pwd)
POCO_BASE = $(MACCHINA_BASE)/platform
PROJECT_BASE = $(MACCHINA_BASE)

export MACCHINA_BASE
export POCO_BASE
export PROJECT_BASE

ifeq ($(TARGET),sdk)
INSTALL_TARGET = install_sdk
else ifeq ($(TARGET),runtime)
INSTALL_TARGET = install_runtime
MAKEARGS = DEFAULT_TARGET=shared_release
else
$(error Invalid TARGET specified: $(TARGET))
endif

osname=$(shell uname)
ifeq ($(osname),Darwin)
VLIBEXT = .*.dylib
LIBEXT = .dylib
else
VLIBEXT = .so.*
LIBEXT = .so
endif

RUNTIME_LIBS = PocoFoundation PocoXML PocoJSON PocoUtil PocoOSP PocoZip

clean all:
	$(MAKE) -C platform $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C server $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C devices $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C protocols $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C services $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C webui $(MAKECMDGOALS) $(MAKEARGS)

install: $(INSTALL_TARGET)

install_sdk:
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/include
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/lib/bundles
	mkdir -p $(INSTALLDIR)/bin	
	$(MAKE) -C platform install INSTALLDIR=$(INSTALLDIR)
	cp -Rf devices/*/include/* $(INSTALLDIR)/include
	cp -Rf protocols/*/include/* $(INSTALLDIR)/include
	cp -Rf services/*/include/* $(INSTALLDIR)/include
	find $(MACCHINA_BASE)/lib -name "libIoT*" -type f -exec cp -f {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/lib -name "libIoT*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/server/bin -perm -700 -type f -name 'macchina*' -exec cp -f {} $(INSTALLDIR)/bin \;
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	rm -f $(INSTALLDIR)/bin/*$(LIBEXT)

install_runtime:
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/lib/bundles
	mkdir -p $(INSTALLDIR)/bin	
	find $(MACCHINA_BASE)/server/bin -perm -700 -type f -name macchina -exec cp -f {} $(INSTALLDIR)/bin \;
	for lib in $(RUNTIME_LIBS) ; do \
		find $(POCO_BASE)/lib -name "lib$$lib$(VLIBEXT)" -type f -exec cp -f {} $(INSTALLDIR)/lib \; ; \
	done
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
