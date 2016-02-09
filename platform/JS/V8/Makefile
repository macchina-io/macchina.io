#
# Makefile
#
# $Id: //poco/1.4/JS/V8/Makefile#5 $
#
# Makefile for v8 JavaScript engine
#

include $(POCO_BASE)/build/rules/global

V8VERSION = 3.28.4
GYPREVISION = 1831
V8BASE = v8-$(V8VERSION)
ifdef V8_NOSNAPSHOT
V8SNAPSHOT = snapshot=off
else
V8SNAPSHOT = snapshot=on
endif
V8FLAGS = library=shared i18nsupport=off werror=no $(V8SNAPSHOT) $(V8_EXTRA_FLAGS)

.PHONY: v8base v8deps

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
V8FLAGS += arm_version=7
endif
ifeq ($(findstring armv6,$(OSARCH)),armv6)
V8FLAGS += arm_version=6
# Workaround for Raspberry Pi
V8FLAGS += armfpu=vfp armfloatabi=hard armneon=off
endif
ifeq ($(findstring mipsel,$(OSARCH)),mipsel)
V8ARCH = mipsel
endif

$(info Building V8 for arch $(V8ARCH) with flags: $(V8FLAGS))

ifeq ($(V8ARCH),)
$(error Unknown target architecture)
endif

ifeq ($(findstring clang,$(CXX)),clang)
GYP_DEFINES += clang=1
CXX += -Wno-tautological-undefined-compare -Wno-inconsistent-missing-override
endif

export GYP_DEFINES

ifneq ($(POCO_TARGET_OSARCH),$(POCO_HOST_OSARCH))
v8targetlibdir = lib.target
endif

# Reduce linker memory usage on ARM systems
ifeq ($(findstring armv7,$(POCO_HOST_OSARCH)),armv7)
LINK += -Xlinker --hash-size=31 -Xlinker --reduce-memory-overhead
export LINK
endif

default: v8install

$(V8BASE): archive/$(V8BASE).tar.gz
	tar xfz $<
	cd $(V8BASE) && patch -p1 <../patches/armv6.patch
	cd $(V8BASE) && patch -p1 <../patches/standalone.patch

v8base: $(V8BASE)

v8deps: v8base
	mkdir -p $(V8BASE)/build
	cd $(V8BASE)/build && tar xfz ../../archive/gyp-$(GYPREVISION).tar.gz
	
shared_debug: v8deps 
	-$(MAKE) -C $(V8BASE) $(V8ARCH).debug $(V8FLAGS) 

shared_release: v8deps
	-$(MAKE) -C $(V8BASE) $(V8ARCH).release $(V8FLAGS) 
	
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
