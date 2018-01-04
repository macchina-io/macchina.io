
add_library(PocoWebTunnel 
    src/RemotePortForwarder.cpp
    src/PortReflector.cpp
    src/TunnelSocket.cpp
    src/Protocol.cpp
    src/SocketDispatcher.cpp
    src/LocalPortForwarder.cpp
    src/TunnelSocketImpl.cpp
)

target_link_libraries(PocoWebTunnel Foundation Net )
target_include_directories(PocoWebTunnel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE 
       src
    )
