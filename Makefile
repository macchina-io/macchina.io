#
# Makefile
#
# $Id$
#
# Global Makefile for macchina.io
#

.PHONY: clean all clean_bundles install_sdk install_runtime install

PRODUCT ?= sdk
DESTDIR ?= /usr/local/macchina
INSTALLDIR ?= $(DESTDIR)

RUNTIME_LIBS = PocoFoundation PocoXML PocoJSON PocoUtil PocoZip PocoOSP PocoRemotingNG PocoGeo

MACCHINA_BASE = $(shell pwd)
POCO_BASE = $(MACCHINA_BASE)/platform
PROJECT_BASE = $(MACCHINA_BASE)

export MACCHINA_BASE
export POCO_BASE
export PROJECT_BASE

ifeq ($(PRODUCT),sdk)
INSTALL_TARGET = install_sdk
else ifeq ($(PRODUCT),runtime)
INSTALL_TARGET = install_runtime
MAKEARGS = DEFAULT_TARGET=shared_release
else
$(error Invalid PRODUCT specified: $(PRODUCT))
endif

POCO_HOST_OSNAME = $(shell uname)
POCO_HOST_OSARCH ?= $(subst /,-,$(shell uname -m | tr ' ' _))

ifeq ($(POCO_HOST_OSNAME),Darwin)
VLIBEXT = .*.dylib
LIBEXT = .dylib
else
VLIBEXT = .so.*
LIBEXT = .so
endif

#
# If POCO_CONFIG is not set, use the OS name as configuration name
#
ifndef POCO_CONFIG
POCO_CONFIG = $(POCO_HOST_OSNAME)
endif

#
# Include System Specific Settings
#
include $(POCO_BASE)/build/config/$(POCO_CONFIG)

#
# Determine operating system
#
ifndef POCO_TARGET_OSNAME
OSNAME := $(POCO_HOST_OSNAME)
else
OSNAME := $(POCO_TARGET_OSNAME)
endif
ifndef POCO_TARGET_OSARCH
OSARCH := $(subst /,-,$(shell uname -m | tr ' ' _))
else
OSARCH := $(POCO_TARGET_OSARCH)
endif


#
# Make Targets
#

# All macchina.io
clean all:
	$(MAKE) -C platform $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C server $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C devices/Devices $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C devices/Serial $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C protocols $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C devices $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C services $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C webui $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C samples $(MAKECMDGOALS) $(MAKEARGS)
	
clean_bundles:
	rm platform/osp/bundles/*.bndl
	rm */bundles/*.bndl

# Host tools only
hosttools:
	$(MAKE) -C platform/Foundation 
	$(MAKE) -C platform/XML 
	$(MAKE) -C platform/JSON 
	$(MAKE) -C platform/Util 
	$(MAKE) -C platform/Net
	$(MAKE) -C platform/Zip
	$(MAKE) -C platform/OSP 
	$(MAKE) -C platform/OSP/BundleCreator 
	$(MAKE) -C platform/OSP/CodeCacheUtility 
	$(MAKE) -C platform/CppParser 
	$(MAKE) -C platform/CodeGeneration 
	$(MAKE) -C platform/RemotingNG
	$(MAKE) -C platform/RemotingNG/RemoteGen 
	$(MAKE) -C platform/PageCompiler 
	$(MAKE) -C platform/PageCompiler/File2Page

install: $(INSTALL_TARGET)

install_sdk:
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/include
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/lib/bundles
	mkdir -p $(INSTALLDIR)/bin	
	mkdir -p $(INSTALLDIR)/etc
	$(MAKE) -C platform install INSTALLDIR=$(INSTALLDIR)
	cp -Rf devices/*/include/* $(INSTALLDIR)/include
	cp -Rf protocols/*/include/* $(INSTALLDIR)/include
	cp -Rf services/*/include/* $(INSTALLDIR)/include
	find $(MACCHINA_BASE)/lib/$(OSNAME)/$(OSARCH) -name "libIoT*" -type f -exec cp -f {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/lib/$(OSNAME)/$(OSARCH) -name "libIoT*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/server/bin/$(OSNAME)/$(OSARCH) -perm -700 -type f -name 'macchina*' -exec cp -f {} $(INSTALLDIR)/bin \;
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	rm -f $(INSTALLDIR)/bin/*$(LIBEXT)
	cp $(MACCHINA_BASE)/server/macchina.properties.install $(INSTALLDIR)/etc/macchina.properties
	cp $(MACCHINA_BASE)/server/rootcert.pem $(INSTALLDIR)/etc
	cp $(MACCHINA_BASE)/server/macchina.pem $(INSTALLDIR)/etc	

install_runtime:
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/lib/bundles
	mkdir -p $(INSTALLDIR)/bin	
	mkdir -p $(INSTALLDIR)/etc
	find $(MACCHINA_BASE)/server/bin/$(OSNAME)/$(OSARCH) -perm -700 -type f -name macchina -exec cp -f {} $(INSTALLDIR)/bin \;
	for lib in $(RUNTIME_LIBS) ; do \
		find $(POCO_BASE)/lib/$(OSNAME)/$(OSARCH) -name "lib$$lib$(VLIBEXT)" -type f -exec cp -f {} $(INSTALLDIR)/lib \; ; \
	done
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp $(MACCHINA_BASE)/server/macchina.properties.install $(INSTALLDIR)/etc/macchina.properties
	cp $(MACCHINA_BASE)/server/rootcert.pem $(INSTALLDIR)/etc
	cp $(MACCHINA_BASE)/server/macchina.pem $(INSTALLDIR)/etc
