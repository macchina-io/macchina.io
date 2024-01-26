#
# Makefile
#
# Global Makefile for macchina.io
#

.PHONY: build clean all clean_bundles install_sdk install_runtime install docs 

PRODUCT ?= sdk
DESTDIR ?= /usr/local/macchina
INSTALLDIR ?= $(DESTDIR)

sinclude components.make

RUNTIME_LIBS = PocoFoundation PocoXML PocoJSON PocoUtil PocoZip PocoOSP PocoRemotingNG PocoGeo

HOST_LIBS = PocoFoundation PocoXML PocoJSON PocoUtil PocoNet PocoZip PocoOSP PocoRemotingNG PocoCppParser PocoCodeGeneration 
HOST_TOOLS = OSP/BundleCreator OSP/CodeCacheUtility OSP/StripBundle RemotingNG/RemoteGen PageCompiler PageCompiler/File2Page 

ifdef MACCHINA_ENABLE_ACTIVERECORD
HOST_TOOLS += ActiveRecord/Compiler
endif

MACCHINA_BASE = $(shell pwd)
POCO_BASE = $(MACCHINA_BASE)/platform
PROJECT_BASE = $(MACCHINA_BASE)

export MACCHINA_BASE
export POCO_BASE
export PROJECT_BASE

# Get SDK_DIRS from SDK.make
include SDK.make

ifeq ($(PRODUCT),sdk)
BUILD_TARGET = all
INSTALL_TARGET = install_sdk
else ifeq ($(PRODUCT),runtime)
BUILD_TARGET = all
INSTALL_TARGET = install_runtime
MAKEARGS = DEFAULT_TARGET=shared_release
else ifeq ($(PRODUCT),hosttools)
BUILD_TARGET = hosttools
INSTALL_TARGET = install_hosttools
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

ifdef ASAN
SANITIZEFLAGS  = -fsanitize=address
EXTRA_GYPFLAGS = -Dasan=1
export SANITIZEFLAGS
export EXTRA_GYPFLAGS
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

build: $(BUILD_TARGET)

# All macchina.io
clean all:
	$(MAKE) -C platform $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C server $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C protocols $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C devices $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C services $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C webui $(MAKECMDGOALS) $(MAKEARGS)
	$(MAKE) -C samples $(MAKECMDGOALS) $(MAKEARGS)

clean_bundles:
	rm platform/OSP/bundles/*.bndl
	rm */bundles/*.bndl

# Host tools only
hosttools:
	$(MAKE) -C platform/Foundation
	$(MAKE) -C platform/XML
	$(MAKE) -C platform/JSON
	$(MAKE) -C platform/Util
	$(MAKE) -C platform/Net
	$(MAKE) -C platform/Zip
ifdef MACCHINA_ENABLE_ACTIVERECORD
	$(MAKE) -C platform/ActiveRecord/Compiler
endif
	$(MAKE) -C platform/OSP
	$(MAKE) -C platform/OSP/BundleCreator
	$(MAKE) -C platform/OSP/CodeCacheUtility
	$(MAKE) -C platform/OSP/StripBundle
	$(MAKE) -C platform/CppParser
	$(MAKE) -C platform/CodeGeneration
	$(MAKE) -C platform/RemotingNG
	$(MAKE) -C platform/RemotingNG/RemoteGen
	$(MAKE) -C platform/PageCompiler
	$(MAKE) -C platform/PageCompiler/File2Page

install: $(INSTALL_TARGET)

install_hosttools:
	install -d $(INSTALLDIR)/lib
	install -d $(INSTALLDIR)/bin
	for comp in $(HOST_TOOLS) ; do \
		if [ -d "platform/$$comp/bin/$(POCO_HOST_OSNAME)/$(POCO_HOST_OSARCH)" ] ; then \
			find platform/$$comp/bin/$(POCO_HOST_OSNAME)/$(POCO_HOST_OSARCH) -perm -700 -type f -exec install {} $(INSTALLDIR)/bin \; ; \
		fi ; \
	done
	for comp in $(HOST_LIBS) ; do \
		find platform/lib/$(POCO_HOST_OSNAME)/$(POCO_HOST_OSARCH) -name "lib$$comp*" -type f -exec cp -f {} $(INSTALLDIR)/lib \; ; \
	done

install_sdk:
	install -d $(INSTALLDIR)/include
	install -d $(INSTALLDIR)/lib
	install -d $(INSTALLDIR)/lib/bundles
	install -d $(INSTALLDIR)/bin
	install -d $(INSTALLDIR)/etc
	$(MAKE) -C platform install INSTALLDIR=$(abspath $(INSTALLDIR))
	for sdk in $(SDK_DIRS) ; do \
		cp -Rf $$sdk/include/* $(INSTALLDIR)/include ;\
	done
	find $(MACCHINA_BASE)/lib/$(OSNAME)/$(OSARCH) -name "libIoT*" -type f -exec cp -f {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/lib/$(OSNAME)/$(OSARCH) -name "libIoT*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;
	find $(MACCHINA_BASE)/server/bin/$(OSNAME)/$(OSARCH) -perm -700 -type f -name 'macchina*' -exec install {} $(INSTALLDIR)/bin \;
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	rm -f $(INSTALLDIR)/bin/*$(LIBEXT)
	cp $(MACCHINA_BASE)/server/macchina.properties.install $(INSTALLDIR)/etc/macchina.properties
	cp $(MACCHINA_BASE)/server/rootcert.pem $(INSTALLDIR)/etc
	cp $(MACCHINA_BASE)/server/macchina.pem $(INSTALLDIR)/etc

install_runtime:
	install -d $(INSTALLDIR)/lib
	install -d $(INSTALLDIR)/lib/bundles
	install -d $(INSTALLDIR)/bin
	install -d $(INSTALLDIR)/etc
	find $(MACCHINA_BASE)/server/bin/$(OSNAME)/$(OSARCH) -perm -700 -type f -name macchina -exec install {} $(INSTALLDIR)/bin \;
	for lib in $(RUNTIME_LIBS) ; do \
		find $(POCO_BASE)/lib/$(OSNAME)/$(OSARCH) -name "lib$$lib$(VLIBEXT)" -type f -exec cp -f {} $(INSTALLDIR)/lib \; ; \
	done
	cp -f $(POCO_BASE)/OSP/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp -f $(MACCHINA_BASE)/*/bundles/*.bndl $(INSTALLDIR)/lib/bundles
	cp $(MACCHINA_BASE)/server/macchina.properties.install $(INSTALLDIR)/etc/macchina.properties
	cp $(MACCHINA_BASE)/server/rootcert.pem $(INSTALLDIR)/etc
	cp $(MACCHINA_BASE)/server/macchina.pem $(INSTALLDIR)/etc
	if [ -d $(POCO_BASE)/OSP/Shell/Client/bin/$(OSNAME)/$(OSARCH) ] ; then \
		find $(POCO_BASE)/OSP/Shell/Client/bin/$(OSNAME)/$(OSARCH) -perm -700 -type f -name ospsh -exec install {} $(INSTALLDIR)/bin \; ; \
	fi

docs: hosttools
	$(MAKE) -C tools/PocoDoc
	tools/PocoDoc/bin/$(POCO_HOST_OSNAME)/$(POCO_HOST_OSARCH)/PocoDoc --config=tools/PocoDoc/cfg/macchina.xml

docker-image:
	docker pull alpine:3.18
	docker build -t macchina/edge .

docker-sdk-image:
	docker pull alpine:3.18
	docker build -f Dockerfile-SDK -t macchina/edge-sdk .
