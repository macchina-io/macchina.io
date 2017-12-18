#
# Makefile
#
# Makefile for v8 JavaScript engine
#

include $(POCO_BASE)/build/rules/global

.PHONY: v8deps

GYPFLAGS = -Dcomponent=shared_library -Dlinux_use_bundled_binutils=0 \
	-Dlinux_use_bundled_gold=0 -Dlinux_use_gold_flags=0 -Dv8_enable_backtrace=0 -Ddcheck_always_on=0 \
	-Dv8_enable_handle_zapping=0 -Dv8_enable_slow_dchecks=0 -Dv8_enable_inspector=0 \
	-Dv8_enable_gdbjit=0 -Dwerror='' -Dtest_isolation_mode=noop -Dv8_optimized_debug=0 \
	-Dv8_enable_i18n_support=0 -Dwant_separate_host_toolset=0 -Dv8_use_external_startup_data=0 \
	-Dv8_random_seed=0

ifdef V8_ENABLE_SNAPSHOT
GYPFLAGS += -Dv8_use_snapshot=true
else
GYPFLAGS += -Dv8_use_snapshot=false
endif

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
GYPFLAGS += -Darm_fpu=default -Darm_float_abi=default -Darm_thumb=0 -Darm_test_noprobe=on
endif
ifeq ($(findstring armv7,$(OSARCH)),armv7)
GYPFLAGS += -Darm_version=7
endif
ifeq ($(OSARCH),mipsel)
V8ARCH = mipsel
endif
ifeq ($(OSARCH),mips)
V8ARCH = mips
endif

ifeq ($(POCO_HOST_OSARCH),x86_64)
V8HOSTARCH = x64
endif
ifeq ($(POCO_HOST_OSARCH),i386)
V8HOSTARCH = ia32
endif
ifeq ($(POCO_HOST_OSARCH),i686)
V8HOSTARCH = ia32
endif
ifeq ($(findstring arm,$(POCO_HOST_OSARCH)),arm)
V8HOSTARCH = arm
endif

GYPFLAGS += -Dv8_target_arch=$(V8ARCH) -Dtarget_arch=$(V8ARCH) -Dhost_arch=$(V8HOSTARCH)

ifeq ($(V8ARCH),)
$(error Unknown target architecture)
endif
ifeq ($(findstring clang,$(CXX)),clang)
GYPFLAGS += -Dclang=1
endif

ifeq ($(POCO_HOST_OSNAME),Linux)
v8targetlibdir = lib.target/
endif

# Reduce linker memory usage on ARM systems
ifeq ($(findstring armv7,$(POCO_HOST_OSARCH)),armv7)
LINK += -Xlinker --hash-size=31 -Xlinker --reduce-memory-overhead
export LINK
endif

default: shared_release

v8deps: out/Makefile include/v8.h

out/Makefile:
	 tools/gyp/gyp $(GYPFLAGS) --generator-output=$(POCO_BASE)/JS/V8/out -Goutput_dir=$(POCO_BASE)/JS/V8/out -f make -Icommon.gypi --depth=. v8/src/v8.gyp

shared_debug: v8deps
	$(MAKE) -C out BUILDTYPE=Debug CFLAGS="$(CFLAGS) $(SHAREDOPT_CC)" CXXFLAGS="$(CXXFLAGS) $(SHAREDOPT_CXX)" v8 v8_libplatform
	cp out/Debug/$(v8targetlibdir)libv8$(SHAREDLIBLINKEXT) $(LIBPATH)
	cp out/Debug/$(v8targetlibdir)libv8_libbase$(SHAREDLIBLINKEXT) $(LIBPATH)
	cp out/Debug/$(v8targetlibdir)libv8_libplatform$(SHAREDLIBLINKEXT) $(LIBPATH)

shared_release: v8deps
	$(MAKE) -C out BUILDTYPE=Release CFLAGS="$(CFLAGS) $(SHAREDOPT_CC)" CXXFLAGS="$(CXXFLAGS) $(SHAREDOPT_CXX)" v8 v8_libplatform
	cp out/Release/$(v8targetlibdir)libv8$(SHAREDLIBLINKEXT) $(LIBPATH)
	cp out/Release/$(v8targetlibdir)libv8_libbase$(SHAREDLIBLINKEXT) $(LIBPATH)
	cp out/Release/$(v8targetlibdir)libv8_libplatform$(SHAREDLIBLINKEXT) $(LIBPATH)

all_shared: shared_debug shared_release

include/v8.h: v8/include/v8.h
	mkdir -p include
	mkdir -p include/libplatform
	cp v8/include/*.h include
	cp v8/include/libplatform/*.h include/libplatform

clean:
	$(RM) out

distclean: clean
	$(RM) include
