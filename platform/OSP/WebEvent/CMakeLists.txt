set(TARGET "com.appinf.osp.webevent")
set(BUNDLE_SPEC "${CMAKE_CURRENT_SOURCE_DIR}/WebEventBundle.bndlspec")

set(LIBNAME "OSPWebEvent")
set(POCO_LIBNAME "Poco${LIBNAME}")
set(LIBVERSION 1)

set(TARGET_BINDIR ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>)
set(BUNDLE_DIR ${CMAKE_BINARY_DIR}/bundles)

# Sources
set(LIB_SRCS
	src/WebEventRequestHandler.cpp
	src/WebEventService.cpp
	src/WebEventServiceImpl.cpp
)

# Version Resource
if(MSVC AND BUILD_SHARED_LIBS)
	source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
	list(APPEND LIB_SRCS ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
endif()

set(BUNDLE_SRCS
	src/WebEventBundleActivator.cpp
)

# Shared Library
add_library(${LIBNAME} ${LIB_SRCS})
add_library(Poco::OSPWebEvent ALIAS ${LIBNAME})
set_target_properties(${LIBNAME}
	PROPERTIES
	VERSION ${LIBVERSION}
	OUTPUT_NAME ${POCO_LIBNAME}
	DEFINE_SYMBOL OSPWebEvent_EXPORTS
)

target_link_libraries(${LIBNAME} PUBLIC Poco::OSPWeb Poco::OSP Poco::Zip Poco::Net Poco::Util Poco::XML Poco::JSON Poco::Foundation)
target_include_directories(${LIBNAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dynamic Library
add_library(${TARGET} MODULE ${BUNDLE_SRCS})
set_target_properties(${TARGET}
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${TARGET_BINDIR}"
	PREFIX ""
)

# On macOS, use .dylib instead of .so
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set_target_properties(${TARGET} PROPERTIES SUFFIX ".dylib")
endif()

target_link_libraries(${TARGET} OSPWebEvent Poco::OSPWeb Poco::OSP Poco::Zip Poco::Net Poco::Util Poco::XML Poco::JSON Poco::Foundation)

# Copy Bundle Resources to build directory
add_custom_command(TARGET ${TARGET}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/bundle ${CMAKE_CURRENT_BINARY_DIR}/bundle
)

# Build Bundle
add_dependencies(${TARGET} BundleCreator)
poco_osp_bundle(${TARGET}-bundle
	DEPENDS ${LIBNAME} ${TARGET}
	SPEC ${BUNDLE_SPEC}
	CODE $<TARGET_FILE:${LIBNAME}> $<TARGET_FILE:${TARGET}>
	DESTINATION ${BUNDLE_DIR}
)

install(
	DIRECTORY ${BUNDLE_DIR}
	DESTINATION lib${LIB_SUFFIX}
)

POCO_INSTALL(${LIBNAME})
POCO_GENERATE_PACKAGE(${LIBNAME})
