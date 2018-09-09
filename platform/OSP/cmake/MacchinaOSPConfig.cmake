#include(CMakeFindDependencyMacro)
#find_dependency(PocoZip PocoUtil PocoXML PocoFoundation)
#include("${CMAKE_CURRENT_LIST_DIR}/PocoOSPTargets.cmake")

macro(create_bundle)
  set(options "")
  set(oneValueArgs TARGET SPEC_FILE)
  set(multiValueArgs "")
  cmake_parse_arguments(CREATE_BUNDLE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  set_target_properties(${CREATE_BUNDLE_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${CREATE_BUNDLE_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})

  add_custom_command(TARGET ${CREATE_BUNDLE_TARGET} POST_BUILD
    COMMAND LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}:${POCOCPP_ROOT}/lib $<TARGET_FILE:bundle> -n${CMAKE_SYSTEM_NAME} -a${CMAKE_SYSTEM_PROCESSOR} -o${CMAKE_BINARY_DIR}/bundles ${CMAKE_CURRENT_SOURCE_DIR}/${CREATE_BUNDLE_SPEC_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endmacro()

