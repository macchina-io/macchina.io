
add_executable(macchina src/MacchinaServer.cpp)

target_link_libraries(macchina PocoOSP PocoZip PocoUtil PocoJSON PocoXML PocoFoundation)

add_custom_command(TARGET macchina POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/macchina.properties.in ${CMAKE_BINARY_DIR}/macchina.properties
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/macchina.pem ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/rootcert.pem ${CMAKE_BINARY_DIR}
)
