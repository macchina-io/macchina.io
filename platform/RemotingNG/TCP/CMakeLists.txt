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

add_library(RemotingNGTCP ${SRCS})
add_library(Poco::RemotingNGTCP ALIAS RemotingNGTCP)
set_target_properties(RemotingNGTCP
	PROPERTIES
	VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
	OUTPUT_NAME PocoRemotingNGTCP
	DEFINE_SYMBOL RemotingNGTCP_EXPORTS
)

target_link_libraries(RemotingNGTCP PUBLIC Poco::Foundation Poco::Net Poco::RemotingNG)
target_include_directories(RemotingNGTCP
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

POCO_INSTALL(RemotingNGTCP)
POCO_GENERATE_PACKAGE(RemotingNGTCP)

if(ENABLE_TESTS)
	add_subdirectory(testsuite)
endif()
