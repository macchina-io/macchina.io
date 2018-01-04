 
add_library(PocoSerial
    src/SerialPort.cpp
    $<$<PLATFORM_ID:"Linux">:src/SerialPort_POSIX.cpp>
    $<$<PLATFORM_ID:"Windows">:src/SerialPort_WIN32.cpp>
)

target_link_libraries(PocoSerial Foundation)
target_include_directories(PocoSerial
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(BeagleBone)
    target_compile_definitions(PocoSerial PUBLIC POCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK)    
endif()
