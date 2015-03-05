#
# Makefile
#
# $Id: //poco/1.4/JS/V8/Makefile#5 $
#
# Makefile for v8 JavaScript engine
#

include $(POCO_BASE)/build/rules/global

V8VERSION = 3.25.28.18
GYPREVISION = 1831
V8BASE = v8-$(V8VERSION)
V8FLAGS = library=shared snapshot=off i18nsupport=off werror=no

.PHONY: v8base v8deps v8libs

ifeq ($(OSARCH),x86_64)
V8ARCH = x64
endif
ifeq ($(OSARCH),i386)
V8ARCH = ia32
endif
ifeq ($(OSARCH),i686)
V8ARCH = ia32
endif
ifeq ($(findstring arm,$(OSARCH)),arm)
V8ARCH = arm
endif
ifeq ($(findstring armv7,$(OSARCH)),armv7)
V8FLAGS += armv7=true
endif
ifeq ($(findstring mipsel,$(OSARCH)),mipsel)
V8ARCH = mipsel
endif

ifeq ($(V8ARCH),)
$(error Unknown target architecture)
endif

ifeq ($(findstring clang,$(CXX)),clang)
GYP_DEFINES += clang=1
endif

export GYP_DEFINES

ifneq ($(POCO_TARGET_OSARCH),$(POCO_HOST_OSARCH))
v8targetlibdir = lib.target
endif

default: v8install

$(V8BASE): archive/$(V8BASE).tar.gz
	tar xfz $<

v8base: $(V8BASE)

v8deps: v8base
	mkdir -p $(V8BASE)/build
	cd $(V8BASE)/build && tar xfz ../../archive/gyp-$(GYPREVISION).tar.gz
	
v8libs: v8deps

shared_debug: v8deps
	$(MAKE) -C $(V8BASE) $(V8ARCH).debug $(V8FLAGS) 

shared_release: v8deps
	$(MAKE) -C $(V8BASE) $(V8ARCH).release $(V8FLAGS) 
	
all_shared: shared_debug shared_release

v8install: $(DEFAULT_TARGET)
	if [ -d $(V8BASE)/out/$(V8ARCH).release ] ; then cp $(V8BASE)/out/$(V8ARCH).release/$(v8targetlibdir)/libv8$(SHAREDLIBLINKEXT) $(LIBPATH) ; fi
	if [ -d $(V8BASE)/out/$(V8ARCH).debug ] ; then cp $(V8BASE)/out/$(V8ARCH).debug/$(v8targetlibdir)/libv8$(SHAREDLIBLINKEXT) $(LIBPATH)/libv8d$(SHAREDLIBLINKEXT) ; fi
	mkdir -p include
	cp $(V8BASE)/include/*.h include

clean:
	-$(MAKE) -C $(V8BASE) clean

distclean:
	$(RM) $(V8BASE)
	$(RM) include
	$(RM) $(LIBPATH)/libv8$(SHAREDLIBLINKEXT)
	$(RM) $(LIBPATH)/libv8d$(SHAREDLIBLINKEXT)
