#
# Makefile
#
# The global Makefile for macchina.io platform
#

ifndef MACCHINA_HAVE_COMPONENTS
sinclude ../components.make
endif

ifndef POCO_BASE
$(warning WARNING: POCO_BASE is not defined. Assuming current directory.)
export POCO_BASE=$(shell pwd)
endif

ifndef POCO_BUILD
export POCO_BUILD=$(POCO_BASE)
endif

.PHONY: poco all libexecs cppunit tests samples clean distclean install

# TESTS and SAMPLES are set in config.make
poco: libexecs $(if $(TESTS),tests) $(if $(SAMPLES),samples)
all: libexecs tests samples

INSTALLDIR = $(DESTDIR)$(POCO_PREFIX)
COMPONENTS = Foundation XML JSON Util Net Zip Crypto NetSSL_OpenSSL CppParser CodeGeneration RemotingNG RemotingNG/RemoteGen RemotingNG/TCP OSP OSP/BundleCreator OSP/CodeCacheUtility OSP/StripBundle OSP/Core OSP/Crypto OSP/Net OSP/NetSSL_OpenSSL

cppunit:
	$(MAKE) -C $(POCO_BASE)/CppUnit

CppUnit-clean:
	$(MAKE) -C $(POCO_BASE)/CppUnit clean

install: libexecs
	install -d $(INSTALLDIR)/include/Poco
	install -d $(INSTALLDIR)/lib
	install -d $(INSTALLDIR)/bin
	for comp in $(COMPONENTS) ; do \
		if [ -d "$(POCO_BASE)/$$comp/include" ] ; then \
			cp -Rf $(POCO_BASE)/$$comp/include/* $(INSTALLDIR)/include/ ; \
		fi ; \
		if [ -d "$(POCO_BUILD)/$$comp/bin" ] ; then \
			find $(POCO_BUILD)/$$comp/bin -perm -700 -type f -exec install {} $(INSTALLDIR)/bin \; ; \
		fi ; \
	done
	find $(POCO_BUILD)/lib -name "libPoco*" -type f -exec cp -f {} $(INSTALLDIR)/lib \;
	find $(POCO_BUILD)/lib -name "libPoco*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;
ifdef MACCHINA_ENABLE_JS
	find $(POCO_BUILD)/lib -name 'libv8.*' -type f -exec cp -f {} $(INSTALLDIR)/lib \;
endif
	mkdir -p $(INSTALLDIR)/build/config
	mkdir -p $(INSTALLDIR)/build/rules
	mkdir -p $(INSTALLDIR)/build/script
	cp $(POCO_BASE)/build/config/* $(INSTALLDIR)/build/config
	cp $(POCO_BASE)/build/rules/* $(INSTALLDIR)/build/rules
	cp $(POCO_BASE)/build/script/* $(INSTALLDIR)/build/script
	mv $(INSTALLDIR)/build/rules/global.sdk $(INSTALLDIR)/build/rules/global
	cp $(POCO_BASE)/RemotingNG/RemoteGen/RemoteGenNG.xml.install $(INSTALLDIR)/bin/RemoteGenNG.xml

# POCO C++ Libraries
libexecs = Foundation-libexec XML-libexec JSON-libexec Util-libexec Net-libexec Crypto-libexec NetSSL_OpenSSL-libexec Zip-libexec PageCompiler-libexec PageCompiler/File2Page-libexec
tests    = Foundation-tests XML-tests JSON-tests Util-tests Net-tests Crypto-tests NetSSL_OpenSSL-tests Zip-tests CppParser-tests
samples  = Foundation-samples XML-samples JSON-samples Util-samples Net-samples Crypto-samples NetSSL_OpenSSL-samples Zip-samples PageCompiler-samples
cleans   = Foundation-clean XML-clean JSON-clean Util-clean Net-clean Crypto-clean NetSSL_OpenSSL-clean Zip-clean PageCompiler-clean PageCompiler/File2Page-clean CppParser-clean

# WebTunnel, JS, Remoting and OSP
libexecs += \
    WebTunnel-libexec \
    CodeGeneration-libexec RemotingNG-libexec RemotingNG/RemoteGen-libexec \
    OSP-libexec OSP/BundleCreator-libexec \
    OSP/CodeCacheUtility-libexec OSP/StripBundle-libexec \
    OSP/Core-libexec OSP/Crypto-libexec OSP/Net-libexec OSP/NetSSL_OpenSSL-libexec \
    OSP/SimpleAuth-libexec \
    Geo-libexec \
    Serial-libexec

tests    += \
	CodeGeneration-tests RemotingNG-tests \
	OSP-tests \
	Geo-tests

samples  += WebTunnel-samples

cleans   += \
    WebTunnel-clean \
    CodeGeneration-clean RemotingNG-clean RemotingNG/RemoteGen-clean \
    OSP-clean OSP/BundleCreator-clean \
    OSP/CodeCacheUtility-clean OSP/StripBundle-clean \
    OSP/Core-clean OSP/Crypto-clean OSP/Net-clean OSP/NetSSL_OpenSSL-clean \
    OSP/SimpleAuth-clean \
    Geo-clean \
    Serial-clean

# Optional Components
ifdef MACCHINA_ENABLE_JS
COMPONENTS += JS/V8 JS/Core JS/File JS/Data JS/Bridge JS/Net JS/Crypto OSP/JS OSP/JS/File OSP/JS/Net OSP/JS/Data OSP/JS/Web OSP/JS/Crypto OSP/JS/Scheduler
libexecs += JS/V8-libexec JS/Core-libexec JS/File-libexec JS/Data-libexec JS/Bridge-libexec JS/Net-libexec JS/Crypto-libexec \
	OSP/JS-libexec OSP/JS/File-libexec OSP/JS/Net-libexec OSP/JS/Data-libexec OSP/JS/Web-libexec OSP/JS/Crypto-libexec OSP/JS/Scheduler-libexec
cleans += JS/V8-clean JS/Core-clean JS/File-clean JS/Data-clean JS/Bridge-clean JS/Net-clean \
	OSP/JS-clean OSP/JS/File-clean OSP/JS/Net-clean OSP/JS/Data-clean OSP/JS/Web-clean OSP/JS/Crypto-clean OSP/JS/Scheduler-clean
endif

ifdef MACCHINA_ENABLE_DATA
COMPONENTS += Data
libexecs   += Data-libexec OSP/Data-libexec
tests      += Data-tests
cleans     += Data-clean OSP/Data-clean

ifdef MACCHINA_ENABLE_DATA_SQLITE
COMPONENTS += Data/SQLite
libexecs   += Data/SQLite-libexec OSP/Data/SQLite-libexec
tests      += Data/SQLite-tests
cleans     += Data/SQLite-clean OSP/Data/SQLite-clean
endif

ifdef MACCHINA_ENABLE_DATA_MYSQL
COMPONENTS += Data/MySQL
libexecs   += Data/MySQL-libexec OSP/Data/MySQL-libexec
tests      += Data/MySQL-tests
cleans     += Data/MySQL-clean OSP/Data/MySQL-clean
endif

ifdef MACCHINA_ENABLE_DATA_ODBC
COMPONENTS += Data/ODBC
libexecs   += Data/ODBC-libexec OSP/Data/ODBC-libexec
tests      += Data/ODBC-tests
cleans     += Data/ODBC-clean OSP/Data/ODBC-clean
endif

ifdef MACCHINA_ENABLE_DATA_POSTGRESQL
COMPONENTS += Data/PostgreSQL
libexecs   += Data/PostgreSQL-libexec OSP/Data/PostgreSQL-libexec
tests      += Data/PostgreSQL-tests
cleans     += Data/PostgreSQL-clean OSP/Data/PostgreSQL-clean
endif

ifdef MACCHINA_ENABLE_ACTIVERECORD
COMPONENTS += ActiveRecord ActiveRecord/Compiler OSP/ActiveRecord
libexecs   += ActiveRecord-libexec ActiveRecord/Compiler-libexec OSP/ActiveRecord-libexec
tests      += ActiveRecord-tests
cleans     += ActiveRecord-clean ActiveRecord/Compiler-clean OSP/ActiveRecord-clean
endif
endif

ifdef MACCHINA_ENABLE_REDIS
COMPONENTS += Redis
libexecs   += Redis-libexec
tests      += Redis-tests
cleans     += Redis-clean
endif

ifdef MACCHINA_ENABLE_MONGODB
COMPONENTS += MongoDB
libexecs   += MongoDB-libexec
tests      += MongoDB-tests
cleans     += MongoDB-clean
endif

ifdef MACCHINA_ENABLE_JWT
COMPONENTS += JWT OSP/JWT
libexecs   += JWT-libexec OSP/JWT-libexec
tests      += JWT-tests
cleans     += JWT-clean OSP/JWT-clean
endif

ifdef MACCHINA_ENABLE_OSP_WEB
COMPONENTS += OSP/Web OSP/WebServer OSP/SecureWebServer
libexecs   += OSP/Web-libexec OSP/WebServer-libexec OSP/SecureWebServer-libexec
tests      += OSP/Web-tests
cleans     += OSP/Web-clean OSP/WebServer-clean OSP/SecureWebServer-clean
ifdef MACCHINA_ENABLE_WEBEVENT
COMPONENTS += OSP/WebEvent
libexecs   += OSP/WebEvent-libexec
cleans     += OSP/WebEvent-clean
endif
endif

ifdef MACCHINA_ENABLE_OSP_MAIL
COMPONENTS += OSP/Mail OSP/SecureMail
libexecs   += OSP/Mail-libexec OSP/SecureMail-libexec
cleans     += OSP/Mail-clean OSP/SecureMail-clean
endif

ifdef MACCHINA_ENABLE_REMOTINGNG_TCP
COMPONENTS += RemotingNG/TCP
libexecs   += RemotingNG/TCP-libexec OSP/RemotingNG/TCP-libexec
tests      += RemotingNG/TCP-tests
cleans     += RemotingNG/TCP-clean OSP/RemotingNG/TCP-clean
endif


.PHONY: $(libexecs)
.PHONY: $(tests)
.PHONY: $(samples)
.PHONY: $(cleans)

libexecs: $(filter-out $(foreach f,$(OMIT),$f%),$(libexecs))
tests: $(filter-out $(foreach f,$(OMIT),$f%),$(tests))
samples: $(filter-out $(foreach f,$(OMIT),$f%),$(samples))
cleans: $(filter-out $(foreach f,$(OMIT),$f%),$(cleans))

Foundation-libexec:
	$(MAKE) -C $(POCO_BASE)/Foundation

Foundation-tests: Foundation-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Foundation/testsuite

Foundation-samples: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Foundation/samples

Foundation-clean:
	$(MAKE) -C $(POCO_BASE)/Foundation clean
	$(MAKE) -C $(POCO_BASE)/Foundation/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Foundation/samples clean

XML-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/XML

XML-tests: XML-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/XML/testsuite

XML-samples: XML-libexec
	$(MAKE) -C $(POCO_BASE)/XML/samples

XML-clean:
	$(MAKE) -C $(POCO_BASE)/XML clean
	$(MAKE) -C $(POCO_BASE)/XML/testsuite clean
	$(MAKE) -C $(POCO_BASE)/XML/samples clean

JSON-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/JSON

JSON-tests: JSON-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/JSON/testsuite

JSON-samples: JSON-libexec
	$(MAKE) -C $(POCO_BASE)/JSON/samples

JSON-clean:
	$(MAKE) -C $(POCO_BASE)/JSON clean
	$(MAKE) -C $(POCO_BASE)/JSON/testsuite clean
	$(MAKE) -C $(POCO_BASE)/JSON/samples clean

Util-libexec: Foundation-libexec XML-libexec JSON-libexec
	$(MAKE) -C $(POCO_BASE)/Util

Util-tests: Util-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Util/testsuite

Util-samples: Util-libexec
	$(MAKE) -C $(POCO_BASE)/Util/samples

Util-clean:
	$(MAKE) -C $(POCO_BASE)/Util clean
	$(MAKE) -C $(POCO_BASE)/Util/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Util/samples clean

Net-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Net

Net-tests: Net-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Net/testsuite

Net-samples: Net-libexec Foundation-libexec XML-libexec Util-libexec
	$(MAKE) -C $(POCO_BASE)/Net/samples

Net-clean:
	$(MAKE) -C $(POCO_BASE)/Net clean
	$(MAKE) -C $(POCO_BASE)/Net/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Net/samples clean

Crypto-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Crypto

Crypto-tests: Crypto-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Crypto/testsuite

Crypto-samples: Crypto-libexec Foundation-libexec Util-libexec
	$(MAKE) -C $(POCO_BASE)/Crypto/samples

Crypto-clean:
	$(MAKE) -C $(POCO_BASE)/Crypto clean
	$(MAKE) -C $(POCO_BASE)/Crypto/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Crypto/samples clean

NetSSL_OpenSSL-libexec: Foundation-libexec Net-libexec Util-libexec Crypto-libexec
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL

NetSSL_OpenSSL-tests: NetSSL_OpenSSL-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/testsuite

NetSSL_OpenSSL-samples: NetSSL_OpenSSL-libexec
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/samples

NetSSL_OpenSSL-clean:
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL clean
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/testsuite clean
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/samples clean

Data-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Data

Data-tests: Data-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/testsuite

Data-samples: Data-libexec Data-libexec Data/SQLite-libexec
	$(MAKE) -C $(POCO_BASE)/Data/samples

Data-clean:
	$(MAKE) -C $(POCO_BASE)/Data clean
	$(MAKE) -C $(POCO_BASE)/Data/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Data/samples clean

Data/SQLite-libexec: Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/SQLite

Data/SQLite-tests: Data/SQLite-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/SQLite/testsuite

Data/SQLite-clean:
	$(MAKE) -C $(POCO_BASE)/Data/SQLite clean
	$(MAKE) -C $(POCO_BASE)/Data/SQLite/testsuite clean

Data/MySQL-libexec: Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/MySQL

Data/MySQL-tests: Data/MySQL-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/MySQL/testsuite

Data/MySQL-clean:
	$(MAKE) -C $(POCO_BASE)/Data/MySQL clean
	$(MAKE) -C $(POCO_BASE)/Data/MySQL/testsuite clean

Data/ODBC-libexec: Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/ODBC

Data/ODBC-tests: Data/ODBC-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/ODBC/testsuite

Data/ODBC-clean:
	$(MAKE) -C $(POCO_BASE)/Data/ODBC clean
	$(MAKE) -C $(POCO_BASE)/Data/ODBC/testsuite clean

Data/PostgreSQL-libexec: Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/PostgreSQL

Data/PostgreSQL-tests: Data/PostgreSQL-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/PostgreSQL/testsuite

Data/PostgreSQL-clean:
	$(MAKE) -C $(POCO_BASE)/Data/PostgreSQL clean
	$(MAKE) -C $(POCO_BASE)/Data/PostgreSQL/testsuite clean

ActiveRecord-libexec: Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/ActiveRecord

ActiveRecord-tests: ActiveRecord-libexec Data/SQLite-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/ActiveRecord/testsuite

ActiveRecord-clean:
	$(MAKE) -C $(POCO_BASE)/ActiveRecord clean
	$(MAKE) -C $(POCO_BASE)/ActiveRecord/testsuite clean

ActiveRecord/Compiler-libexec: Foundation-libexec Util-libexec
	$(MAKE) -C $(POCO_BASE)/ActiveRecord/Compiler

ActiveRecord/Compiler-clean:
	$(MAKE) -C $(POCO_BASE)/ActiveRecord/Compiler clean

Zip-libexec: Foundation-libexec Net-libexec Util-libexec XML-libexec
	$(MAKE) -C $(POCO_BASE)/Zip

Zip-tests: Zip-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Zip/testsuite

Zip-samples: Zip-libexec
	$(MAKE) -C $(POCO_BASE)/Zip/samples

Zip-clean:
	$(MAKE) -C $(POCO_BASE)/Zip clean
	$(MAKE) -C $(POCO_BASE)/Zip/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Zip/samples clean

JWT-libexec: Foundation-libexec JSON-libexec Crypto-libexec
	$(MAKE) -C $(POCO_BASE)/JWT

JWT-tests: JWT-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/JWT/testsuite

JWT-clean:
	$(MAKE) -C $(POCO_BASE)/JWT clean
	$(MAKE) -C $(POCO_BASE)/JWT/testsuite clean

WebTunnel-libexec: Foundation-libexec Net-libexec Util-libexec XML-libexec
	$(MAKE) -C $(POCO_BASE)/WebTunnel

WebTunnel-samples: WebTunnel-libexec
	$(MAKE) -C $(POCO_BASE)/WebTunnel/samples

WebTunnel-clean:
	$(MAKE) -C $(POCO_BASE)/WebTunnel clean

PageCompiler-libexec: Net-libexec Util-libexec XML-libexec Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/PageCompiler

PageCompiler-samples: PageCompiler-libexec
	$(MAKE) -C $(POCO_BASE)/PageCompiler/samples

PageCompiler-clean:
	$(MAKE) -C $(POCO_BASE)/PageCompiler clean
	$(MAKE) -C $(POCO_BASE)/PageCompiler/samples clean

PageCompiler/File2Page-libexec: Net-libexec Util-libexec XML-libexec Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/PageCompiler/File2Page

PageCompiler/File2Page-clean:
	$(MAKE) -C $(POCO_BASE)/PageCompiler/File2Page clean

CppParser-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/CppParser

CppParser-tests: CppParser-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/CppParser/testsuite

CppParser-clean:
	$(MAKE) -C $(POCO_BASE)/CppParser clean
	$(MAKE) -C $(POCO_BASE)/CppParser/testsuite clean

CodeGeneration-libexec: Foundation-libexec CppParser-libexec
	$(MAKE) -C $(POCO_BASE)/CodeGeneration

CodeGeneration-tests: CodeGeneration-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/CodeGeneration/testsuite

CodeGeneration-clean:
	$(MAKE) -C $(POCO_BASE)/CodeGeneration clean
	$(MAKE) -C $(POCO_BASE)/CodeGeneration/testsuite clean

JS/V8-libexec:
	$(MAKE) -C $(POCO_BASE)/JS/V8

JS/V8-clean:
	$(MAKE) -C $(POCO_BASE)/JS/V8 clean

JS/Core-libexec: Foundation-libexec XML-libexec Util-libexec JS/V8-libexec
	$(MAKE) -C $(POCO_BASE)/JS/Core

JS/Core-clean:
	$(MAKE) -C $(POCO_BASE)/JS/Core clean

JS/File-libexec: Foundation-libexec JS/Core-libexec
	$(MAKE) -C $(POCO_BASE)/JS/File

JS/File-clean:
	$(MAKE) -C $(POCO_BASE)/JS/File clean

JS/Data-libexec: Foundation-libexec Data-libexec JS/Core-libexec
	$(MAKE) -C $(POCO_BASE)/JS/Data

JS/Data-clean:
	$(MAKE) -C $(POCO_BASE)/JS/Data clean

JS/Bridge-libexec: Foundation-libexec RemotingNG-libexec JS/Core-libexec
	$(MAKE) -C $(POCO_BASE)/JS/Bridge

JS/Bridge-clean:
	$(MAKE) -C $(POCO_BASE)/JS/Bridge clean

JS/Net-libexec: Foundation-libexec Net-libexec JS/Core-libexec
	$(MAKE) -C $(POCO_BASE)/JS/Net

JS/Net-clean:
	$(MAKE) -C $(POCO_BASE)/JS/Net clean

JS/Crypto-libexec: Foundation-libexec Crypto-libexec JS/Core-libexec
	$(MAKE) -C $(POCO_BASE)/JS/Crypto

JS/Crypto-clean:
	$(MAKE) -C $(POCO_BASE)/JS/Crypto clean

RemotingNG-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/RemotingNG

RemotingNG-tests: RemotingNG-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/RemotingNG/testsuite

RemotingNG-clean:
	$(MAKE) -C $(POCO_BASE)/RemotingNG clean
	$(MAKE) -C $(POCO_BASE)/RemotingNG/testsuite clean

RemotingNG/RemoteGen-libexec: RemotingNG-libexec CodeGeneration-libexec Net-libexec Util-libexec CppParser-libexec XML-libexec Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/RemotingNG/RemoteGen

RemotingNG/RemoteGen-clean:
	$(MAKE) -C $(POCO_BASE)/RemotingNG/RemoteGen clean

RemotingNG/TCP-libexec: RemotingNG-libexec Net-libexec Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/RemotingNG/TCP

RemotingNG/TCP-tests: RemotingNG/TCP-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/RemotingNG/TCP/testsuite

RemotingNG/TCP-clean:
	$(MAKE) -C $(POCO_BASE)/RemotingNG/TCP clean
	$(MAKE) -C $(POCO_BASE)/RemotingNG/TCP/testsuite clean

OSP-libexec: Foundation-libexec XML-libexec Util-libexec Zip-libexec
	$(MAKE) -C $(POCO_BASE)/OSP

OSP-tests: OSP-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/OSP/testsuite

OSP-clean:
	$(MAKE) -C $(POCO_BASE)/OSP clean
	$(MAKE) -C $(POCO_BASE)/OSP/testsuite clean

OSP/BundleCreator-libexec: Foundation-libexec XML-libexec Util-libexec Zip-libexec OSP-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/BundleCreator

OSP/BundleCreator-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/BundleCreator clean

OSP/CodeCacheUtility-libexec: Foundation-libexec XML-libexec Util-libexec Zip-libexec OSP-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/CodeCacheUtility

OSP/CodeCacheUtility-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/CodeCacheUtility clean

OSP/StripBundle-libexec: Foundation-libexec XML-libexec Util-libexec Zip-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/StripBundle

OSP/StripBundle-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/StripBundle clean

OSP/Web-libexec: Net-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Web

OSP/Web-tests: OSP/Web-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/OSP/Web/testsuite

OSP/Web-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Web clean
	$(MAKE) -C $(POCO_BASE)/OSP/Web/testsuite clean

OSP/Core-libexec: OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Core

OSP/Core-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Core clean

OSP/Crypto-libexec: Crypto-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Crypto

OSP/Crypto-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Crypto clean

OSP/Data-libexec: Data-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Data

OSP/Data-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Data clean

OSP/Data/SQLite-libexec: Data-libexec Data/SQLite-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Data/SQLite

OSP/Data/SQLite-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Data/SQLite clean

OSP/Data/MySQL-libexec: Data-libexec Data/MySQL-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Data/MySQL

OSP/Data/MySQL-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Data/MySQL clean

OSP/Data/ODBC-libexec: Data-libexec Data/ODBC-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Data/ODBC

OSP/Data/ODBC-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Data/ODBC clean

OSP/Data/PostgreSQL-libexec: Data-libexec Data/PostgreSQL-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Data/PostgreSQL

OSP/Data/PostgreSQL-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Data/PostgreSQL clean

OSP/ActiveRecord-libexec: ActiveRecord-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/ActiveRecord

OSP/ActiveRecord-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/ActiveRecord clean

OSP/Net-libexec: Net-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Net

OSP/Net-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Net clean

OSP/NetSSL_OpenSSL-libexec: Net-libexec NetSSL_OpenSSL-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/NetSSL_OpenSSL

OSP/NetSSL_OpenSSL-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/NetSSL_OpenSSL clean

OSP/SecureWebServer-libexec: NetSSL_OpenSSL-libexec OSP-libexec OSP/Web-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/SecureWebServer

OSP/SecureWebServer-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/SecureWebServer clean

OSP/WebServer-libexec: OSP-libexec OSP/Web-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/WebServer

OSP/WebServer-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/WebServer clean

OSP/Mail-libexec: OSP-libexec Net-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/Mail

OSP/Mail-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/Mail clean

OSP/SecureMail-libexec: OSP-libexec OSP/Mail-libexec NetSSL_OpenSSL-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/SecureMail

OSP/SecureMail-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/SecureMail clean

OSP/JS-libexec: Foundation-libexec XML-libexec Util-libexec Net-libexec JS/Core-libexec JS/Bridge-libexec JS/Net-libexec JS/Data-libexec OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS

OSP/JS-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS clean

OSP/JS/File-libexec: JS/File-libexec OSP/JS-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/File

OSP/JS/File-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/File clean

OSP/JS/Net-libexec: JS/Net-libexec OSP/JS-libexec Net-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Net

OSP/JS/Net-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Net clean

OSP/JS/Data-libexec: JS/Data-libexec OSP/JS-libexec Data-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Data

OSP/JS/Data-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Data clean

OSP/JS/Web-libexec: OSP/JS-libexec OSP/Web-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Web

OSP/JS/Web-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Web clean

OSP/JS/Crypto-libexec: JS/Crypto-libexec OSP/JS-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Crypto

OSP/JS/Crypto-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Crypto clean

OSP/JS/Scheduler-libexec: OSP/JS-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Scheduler

OSP/JS/Scheduler-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JS/Scheduler clean

OSP/WebEvent-libexec: Net-libexec OSP-libexec OSP/BundleCreator-libexec OSP/Web-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/WebEvent

OSP/WebEvent-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/WebEvent clean

OSP/SimpleAuth-libexec: OSP-libexec OSP/BundleCreator-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/SimpleAuth

OSP/SimpleAuth-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/SimpleAuth clean

OSP/JWT-libexec: OSP/Web-libexec OSP-libexec OSP/BundleCreator-libexec JWT-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/JWT

OSP/JWT-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/JWT clean

OSP/RemotingNG/TCP-libexec: OSP-libexec OSP/BundleCreator-libexec RemotingNG/TCP-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/RemotingNG/TCP

OSP/RemotingNG/TCP-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/RemotingNG/TCP clean

OSP/RemotingNG/REST-libexec: OSP-libexec OSP/BundleCreator-libexec RemotingNG/REST-libexec
	$(MAKE) -C $(POCO_BASE)/OSP/RemotingNG/REST

OSP/RemotingNG/REST-clean:
	$(MAKE) -C $(POCO_BASE)/OSP/RemotingNG/REST clean

Geo-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Geo

Geo-tests: Geo-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Geo/testsuite

Geo-clean:
	$(MAKE) -C $(POCO_BASE)/Geo clean
	$(MAKE) -C $(POCO_BASE)/Geo/testsuite clean

Serial-libexec: Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Serial

Serial-clean:
	$(MAKE) -C $(POCO_BASE)/Serial clean

Redis-libexec: Foundation-libexec Net-libexec
	$(MAKE) -C $(POCO_BASE)/Redis

Redis-tests: Redis-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Redis/testsuite

Redis-clean:
	$(MAKE) -C $(POCO_BASE)/Redis clean
	$(MAKE) -C $(POCO_BASE)/Redis/testsuite clean

MongoDB-libexec: Foundation-libexec Net-libexec
	$(MAKE) -C $(POCO_BASE)/MongoDB

MongoDB-tests: MongoDB-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/MongoDB/testsuite

MongoDB-clean:
	$(MAKE) -C $(POCO_BASE)/MongoDB clean
	$(MAKE) -C $(POCO_BASE)/MongoDB/testsuite clean

clean: cleans CppUnit-clean

distclean:
	rm -rf $(POCO_BUILD)/lib
	find $(POCO_BUILD) -name obj -type d -print0 | xargs -0 rm -rf
	find $(POCO_BUILD) -name .dep -type d -print0 | xargs -0 rm -rf
	find $(POCO_BUILD) -name bin -type d -print0 | xargs -0 rm -rf

