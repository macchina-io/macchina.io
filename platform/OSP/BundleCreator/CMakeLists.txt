# Sources
file(GLOB SRCS "src/*.cpp")

# Version Resource
if(MSVC)
	source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
	list(APPEND SRCS ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
endif()

add_executable(BundleCreator ${SRCS})
set_target_properties(BundleCreator
    PROPERTIES
    OUTPUT_NAME bundle
    )

target_link_libraries(BundleCreator Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation)

install(
    TARGETS BundleCreator EXPORT BundleCreatorTargets
    LIBRARY DESTINATION lib${LIB_SUFFIX}
    ARCHIVE DESTINATION lib${LIB_SUFFIX}
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )
install(EXPORT BundleCreatorTargets
  FILE
    BundleCreatorTargets.cmake
  NAMESPACE
    Poco::OSP::
  DESTINATION
    lib${LIB_SUFFIX}/cmake/Poco
)

# When cross compiling it is assumed that the bundle is already in PATH
if(CMAKE_CROSSCOMPILING)
    find_program(POCO_OSP_BUNDLER NAMES "bundle")
    if(NOT POCO_OSP_BUNDLER)
      message(FATAL_ERROR "Poco::OSP:BundleCreator (bundle) not found in PATH.")
    endif()
    add_executable(Poco::OSP::BundleCreator IMPORTED GLOBAL)
    set_target_properties(Poco::OSP::BundleCreator PROPERTIES IMPORTED_LOCATION "${POCO_OSP_BUNDLER}")
else()
    add_executable(Poco::OSP::BundleCreator ALIAS BundleCreator)
endif(CMAKE_CROSSCOMPILING)
