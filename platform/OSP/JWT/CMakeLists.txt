set(TARGET "poco.jwt")
set(BUNDLE_SPEC "${CMAKE_CURRENT_SOURCE_DIR}/JWT.bndlspec")

set(TARGET_BINDIR ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>)
set(BUNDLE_DIR ${CMAKE_BINARY_DIR}/bundles)

# Sources
file(GLOB SRCS "src/*.cpp")

file(GLOB_RECURSE HDRS_G "src/*.h")
POCO_HEADERS_AUTO(SRCS ${HDRS_G})

# Dynamic Library
add_library(${TARGET} MODULE ${SRCS})
set_target_properties(${TARGET}
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${TARGET_BINDIR}"
	PREFIX ""
)

# On macOS, use .dylib instead of .so
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set_target_properties(${TARGET} PROPERTIES SUFFIX ".dylib")
endif()

target_link_libraries(${TARGET} Poco::OSPWeb Poco::OSP Poco::JWT Poco::Crypto Poco::Zip Poco::Net Poco::Util Poco::XML Poco::JSON Poco::Foundation)

# Build Bundle
add_dependencies(${TARGET} BundleCreator)
poco_osp_bundle(${TARGET}-bundle
	DEPENDS ${LIBNAME} ${TARGET}
	SPEC ${BUNDLE_SPEC}
	CODE $<TARGET_FILE:JWT> $<TARGET_FILE:${TARGET}>
	DESTINATION ${BUNDLE_DIR}
)

install(
	DIRECTORY ${BUNDLE_DIR}
	DESTINATION lib${LIB_SUFFIX}
)
