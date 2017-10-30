 
# BeagleBone needs a special hack to enable
# RS-485 RTS via GPIO. Try to detect BeagleBone
# and enable hack.
# ifeq ($(findstring bone,$(shell uname -r)),bone)
# $(info BeagleBone detected - enabling RS485 hack)
# POCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK = 1
# endif
# 
# ifdef POCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK
# SYSFLAGS += -DPOCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK
# endif
# 
# objects = SerialPort
# 
# target         = PocoSerial
# target_version = 1
# target_libs    = PocoFoundation

set(LIBNAME "Serial")
set(POCO_LIBNAME "Poco${LIBNAME}")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
POCO_HEADERS_AUTO( SRCS ${HDRS_G})

add_library( "${LIBNAME}" ${LIB_MODE} ${SRCS} )
add_library( "${POCO_LIBNAME}" ALIAS "${LIBNAME}")

target_link_libraries( "${LIBNAME}" Foundation )
target_include_directories( "${LIBNAME}"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
target_compile_definitions("${LIBNAME}" PUBLIC ${LIB_MODE_DEFINITIONS})

if(BeagleBone)
    target_compile_definitions("${LIBNAME}" PUBLIC POCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK)    
endif()

POCO_INSTALL("${LIBNAME}")
POCO_GENERATE_PACKAGE("${LIBNAME}")
