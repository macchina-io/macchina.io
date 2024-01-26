set(TARGET "com.appinf.osp.samples.webecho")
set(BUNDLE_SPEC "${CMAKE_CURRENT_SOURCE_DIR}/WebEcho.bndlspec")

set(TARGET_BINDIR ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>)
set(BUNDLE_DIR ${CMAKE_BINARY_DIR}/bundles)

# Sources
file(GLOB TARGET_SRCS "src/*.cpp")

# Dynamic Library
add_library(${TARGET} MODULE ${TARGET_SRCS})
set_target_properties(${TARGET}
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${TARGET_BINDIR}"
	PREFIX ""
)

# On macOS, use .dylib instead of .so
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set_target_properties(${TARGET} PROPERTIES SUFFIX ".dylib")
endif()

target_link_libraries(${TARGET} Poco::OSPWeb Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation)

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
	CODE $<TARGET_FILE:${TARGET}>
	DESTINATION ${BUNDLE_DIR}
)

install(
	DIRECTORY ${BUNDLE_DIR}
	DESTINATION lib${LIB_SUFFIX}
)
