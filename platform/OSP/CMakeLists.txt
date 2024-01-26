# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h")
POCO_HEADERS_AUTO(SRCS ${HDRS_G})

# Version Resource
if(MSVC AND BUILD_SHARED_LIBS)
	source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
	list(APPEND SRCS ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
endif()

add_library(OSP ${SRCS})
add_library(Poco::OSP ALIAS OSP)
set_target_properties(OSP
	PROPERTIES
	VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
	OUTPUT_NAME PocoOSP
	DEFINE_SYMBOL OSP_EXPORTS
)

target_link_libraries(OSP PUBLIC Poco::Foundation Poco::XML Poco::Util Poco::Zip)
target_include_directories(OSP
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

POCO_INSTALL(OSP)
POCO_GENERATE_PACKAGE(OSP)

if(ENABLE_TESTS)
	add_subdirectory(testsuite)
	add_subdirectory(samples)
endif()
