
add_library(PocoGeo  
    src/LatLon.cpp                                                                                                                                                                                                                        
    src/Angle.cpp
)

target_link_libraries(PocoGeo Poco::Foundation)
target_include_directories(PocoGeo
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE 
        src
    )
add_library(Poco::Geo ALIAS PocoGeo)
