cmake_minimum_required(VERSION 3.2.0)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/Bjoe/hunter/archive/026b81652febb03e3e6e2519868dc59d84de2dfe.zip"
    SHA1 "fac046931de6f4762f2d9d321494af8b00aba1bf"
    LOCAL
)

project(macchina.io)

hunter_add_package(PocoCpp)

# Read the version information from the VERSION file
file (STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
message(STATUS "macchina.io version: ${PACKAGE_VERSION}")
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})

set(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})

# Append our module directory to CMake
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/OSP/cmake)

find_package(Poco REQUIRED Foundation Data Crypto JSON Net NetSSL   Util XML Zip) # TODO(BJoe) Add support for CppUnit PageCompiler Redis
# Build third party libraries
#add_subdirectory(platform)
add_subdirectory(platform/Serial)
add_subdirectory(platform/WebTunnel)
add_subdirectory(platform/RemotingNG)
add_subdirectory(platform/Geo)
# add_subdirectory(platform/JS/V8) TODO(BJoe) Fix build error


# Build OSP
add_subdirectory(platform/OSP/BundleCreator)
add_subdirectory(platform/OSP)
add_subdirectory(platform/OSP/CodeCacheUtility)

# Build core bundles
add_subdirectory(platform/OSP/Core)
add_subdirectory(platform/OSP/Net)
add_subdirectory(platform/OSP/Web)

# Build sample
add_subdirectory(platform/OSP/samples/WebInfo)
add_subdirectory(platform/OSP/samples/ServiceListener)

add_subdirectory(launcher)
add_subdirectory(server)

add_dependencies(osp.core bundle)
add_dependencies(poco.net bundle) 
add_dependencies(osp.web bundle)
add_dependencies(com.appinf.osp.samples.servicelistener bundle)

install(EXPORT OSP NAMESPACE Poco:: DESTINATION lib/cmake/macchina)
install(EXPORT Web NAMESPACE Poco::OSP:: DESTINATION lib/cmake/macchina)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/platform/OSP/cmake/MacchinaOSPConfig.cmake
  DESTINATION lib/cmake/macchina)
