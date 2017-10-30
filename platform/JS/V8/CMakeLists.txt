 
include(ExternalProject)

set(V8VERSION "3.28.4")
set(GYPREVISION "1831")

set(V8BASE "v8-${V8VERSION}")

if(V8_SNAPSHOT)
set(V8SNAPSHOT snapshot=on)
else()
set(V8SNAPSHOT snapshot=off)
endif()

set(V8FLAGS library=shared i18nsupport=off werror=no ${V8SNAPSHOT} ${V8_EXTRA_FLAGS})


if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(V8ARCH x64)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "i386")
    set(V8ARCH ia32)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
    set(V8ARCH ia32)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(V8ARCH arm)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7")
    set(V8ARCH arm)
    set(V8FLAGS "${V8FLAGS} arm_version=7")
    # Reduce linker memory usage on ARM systems
    set(LINK "-Xlinker --hash-size=31 -Xlinker --reduce-memory-overhead")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv6")
    set(V8ARCH arm)
    set(V8FLAGS ${V8FLAGS} arm_version=6)
    # Workaround for Raspberry Pi
    set(V8FLAGS ${V8FLAGS} armfpu=vfp armfloatabi=hard armneon=off)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
    set(V8ARCH mipsel)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "mips")
    set(V8ARCH mips)
else()
    message(FATAL_ERROR "Unknown target architecture ${CMAKE_SYSTEM_PROCESSOR}")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(GYP_DEFINES "clang=1")
    if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(GYP_DEFINES "mac_deployment_target=10.9")
    endif()
    set(V8FLAGS ${V8FLAGS} -Wno-tautological-undefined-compare -Wno-inconsistent-missing-override -Wno-shift-negative-value)
endif()

if (NOT CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
    set(v8targetlibdir "lib.target")
endif()

set(V8_ENV "CFLAGS=${CMAKE_C_FLAGS}" "CXXFLAGS=${CMAKE_CXX_FLAGS}" "LINKFLAGS=" "GYP_DEFINES=${GYP_DEFINES}" "LINK=${LINK}")

ExternalProject_Add(
  v8
  URL ${CMAKE_CURRENT_SOURCE_DIR}/archive/${V8BASE}.tar.gz
  BUILD_IN_SOURCE 1
  SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${V8BASE}
  PATCH_COMMAND ${CMAKE_COMMAND} -DPATCH_WORKING_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}/${V8BASE} -DPATCH_DIR=${CMAKE_CURRENT_SOURCE_DIR}/patches -P ${CMAKE_SOURCE_DIR}/cmake/apply_patches.cmake &&
                ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/${V8BASE}/build" && 
                ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/${V8BASE}/build" tar xfz  "${CMAKE_CURRENT_SOURCE_DIR}/archive/gyp-${GYPREVISION}.tar.gz"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND  
    env ${V8_ENV} make ${V8ARCH}.debug ${V8FLAGS} &&
    env ${V8_ENV} make ${V8ARCH}.release ${V8FLAGS}
  INSTALL_COMMAND 
    ${CMAKE_COMMAND} -E copy "include/*.h" "include" &&
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${V8BASE}/out/${V8ARCH}.release/${v8targetlibdir}/libv8.so" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libv8.so" &&
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${V8BASE}/out/${V8ARCH}.debug/${v8targetlibdir}/libv8d.so" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libv8d.so" &&
)
