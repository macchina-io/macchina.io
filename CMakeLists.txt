cmake_minimum_required(VERSION 3.6)
project(macchina.io)

option(POCO_VERBOSE_MESSAGES "Enable informational messages during configure" ON)

file(STRINGS "${PROJECT_SOURCE_DIR}/libversion" SHARED_LIBRARY_VERSION)

# Read the version information from the VERSION file
file (STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
if(POCO_VERBOSE_MESSAGES)
    message(STATUS "Poco package version: ${PACKAGE_VERSION}")
endif()
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})

set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Unstable-trunk")
set(PROJECT_VERSION ${COMPLETE_VERSION})
set(CMAKE_C_STANDARD 99)

set(OSNAME ${CMAKE_SYSTEM_NAME})
set(OSARCH ${CMAKE_SYSTEM_PROCESSOR})

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${OSNAME}/${OSARCH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${OSNAME}/${OSARCH})
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Append our module directory to CMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/macchina.io ${CMAKE_BINARY_DIR}/Poco)

if(POCO_STATIC)
    set(LIB_MODE_DEFINITIONS -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS)
    set(LIB_MODE STATIC)
    if(POCO_VERBOSE_MESSAGES)
        message(STATUS "Building static libraries")
    endif()
else(POCO_STATIC)
    set(LIB_MODE SHARED)
    set(LIB_MODE_DEFINITIONS -DPOCO_NO_AUTOMATIC_LIBS)
    if(POCO_VERBOSE_MESSAGES)
        message(STATUS "Building dynamic libraries")
    endif()
endif(POCO_STATIC)

set(ENABLE_MONGODB OFF CACHE BOOL "Enable MongoDB" FORCE)
set(ENABLE_PDF OFF  CACHE BOOL  "Enable PDF" FORCE)
set(ENABLE_DATA_MYSQL OFF  CACHE BOOL  "Enable Data MySQL" FORCE)
set(ENABLE_DATA_POSTGRESQL OFF  CACHE BOOL "Enable Data PosgreSQL" FORCE)
set(ENABLE_DATA_ODBC OFF  CACHE BOOL "Enable Data ODBC" FORCE)
set(ENABLE_SEVENZIP OFF  CACHE BOOL "Enable SevenZip" FORCE)
set(ENABLE_APACHECONNECTOR OFF  CACHE BOOL "Enable ApacheConnector" FORCE)
set(ENABLE_CPPPARSER OFF  CACHE BOOL "Enable C++ parser" FORCE)
set(ENABLE_POCODOC OFF  CACHE BOOL "Enable Poco Documentation Generator" FORCE)

# Build third party libraries
add_subdirectory(platform)
add_subdirectory(platform/Serial)
add_subdirectory(platform/WebTunnel)
add_subdirectory(platform/RemotingNG)
add_subdirectory(platform/Geo)
# add_subdirectory(platform/JS/V8) TODO Fix build error


# Build OSP
add_subdirectory(platform/OSP/BundleCreator)
add_subdirectory(platform/OSP)
add_subdirectory(platform/OSP/CodeCacheUtility)

# Build core bundles
add_subdirectory(platform/OSP/Core)
add_subdirectory(platform/OSP/Net)
add_subdirectory(platform/OSP/Web)

# Build sample
#add_subdirectory(platform/OSP/samples/WebInfo)
add_subdirectory(platform/OSP/samples/ServiceListener)

add_dependencies(osp.core bundle)
add_dependencies(poco.net bundle) 
add_dependencies(osp.web bundle)
add_dependencies(com.appinf.osp.samples.servicelistener bundle)
