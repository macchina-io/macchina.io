 
set(OSNAME ${CMAKE_SYSTEM_NAME})
set(OSARCH ${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${OSNAME}/${OSARCH})

add_library(com.appinf.osp.samples.webinfo SHARED src/WebInfo.cpp)
target_include_directories(com.appinf.osp.samples.webinfo PUBLIC include)
set_target_properties(com.appinf.osp.samples.webinfo PROPERTIES PREFIX "")
target_link_libraries(com.appinf.osp.samples.webinfo PocoOSP PocoNet PocoUtil PocoXML PocoFoundation)
 
add_custom_command(TARGET com.appinf.osp.samples.webinfo POST_BUILD
   COMMAND ${CMAKE_BINARY_DIR}/bin/bundle -n${OSNAME} -a${OSARCH} -o${CMAKE_BINARY_DIR}/bundles ${CMAKE_CURRENT_SOURCE_DIR}/Net.bndlspec
   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(com.appinf.osp.samples.webinfo bundle)
