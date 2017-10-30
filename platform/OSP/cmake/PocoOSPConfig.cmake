#include(CMakeFindDependencyMacro)
#find_dependency(PocoZip PocoUtil PocoXML PocoFoundation)
#include("${CMAKE_CURRENT_LIST_DIR}/PocoOSPTargets.cmake")

set(OSNAME ${CMAKE_SYSTEM_NAME})
set(OSARCH ${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${OSNAME}/${OSARCH})


macro(create_bundle)
  set(options "")
  set(oneValueArgs TARGET SPEC_FILE)
  set(multiValueArgs "")
  cmake_parse_arguments(CREATE_BUNDLE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  set_target_properties(${CREATE_BUNDLE_TARGET} PROPERTIES PREFIX "")

  add_custom_command(TARGET ${CREATE_BUNDLE_TARGET} POST_BUILD
    COMMAND ${CMAKE_BINARY_DIR}/bin/bundle -n${OSNAME} -a${OSARCH} -o${CMAKE_BINARY_DIR}/bundles ${CMAKE_CURRENT_SOURCE_DIR}/${CREATE_BUNDLE_SPEC_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endmacro()

