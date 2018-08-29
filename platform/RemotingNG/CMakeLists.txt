
add_library(PocoRemotingNG 
    src/URIUtility.cpp
    src/Serializer.cpp
    src/EventListener.cpp
    src/Proxy.cpp
    src/Listener.cpp
    src/ServerTransport.cpp
    src/EventSubscriber.cpp
    src/ProxyFactory.cpp
    src/AttributedObject.cpp
    src/Context.cpp
    src/Authenticator.cpp
    src/RemoteObject.cpp
    src/Transport.cpp
    src/Deserializer.cpp
    src/BinaryDeserializer.cpp
    src/MethodHandler.cpp
    src/BinarySerializer.cpp
    src/TransportFactoryManager.cpp
    src/ORB.cpp
    src/ProxyFactoryManager.cpp
    src/EventDispatcher.cpp
    src/Skeleton.cpp
    src/Credentials.cpp
    src/RemotingException.cpp
    src/SerializerBase.cpp
    src/TransportFactory.cpp
    src/Identifiable.cpp
    src/Authorizer.cpp
)

target_compile_definitions(PocoRemotingNG PUBLIC RemotingNG_EXPORTS)

target_link_libraries(PocoRemotingNG Poco::Foundation)

target_include_directories(PocoRemotingNG
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE 
        src
    )

add_library(Poco::RemotingNG ALIAS PocoRemotingNG)
