# SHAREDOPT_CXX   += -DRemotingNG_EXPORTS
# 
# objects = SerializerBase Serializer Deserializer \
# 	BinarySerializer BinaryDeserializer \
# 	Transport TransportFactory TransportFactoryManager \
# 	ServerTransport Listener Context \
# 	Authorizer Authenticator Credentials \
# 	Proxy ProxyFactory ProxyFactoryManager \
# 	Identifiable RemoteObject Skeleton MethodHandler \
# 	EventDispatcher EventListener EventSubscriber \
# 	ORB \
# 	AttributedObject RemotingException URIUtility
# 
# target         = PocoRemotingNG
# target_version = $(LIBVERSION)
# target_libs    = PocoFoundation $(POCO_LICENSING)

set(LIBNAME "RemotingNG")
set(POCO_LIBNAME "Poco${LIBNAME}")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
POCO_HEADERS_AUTO( SRCS ${HDRS_G})

add_library( "${LIBNAME}" ${LIB_MODE} ${SRCS} )
add_library( "${POCO_LIBNAME}" ALIAS "${LIBNAME}")
set_target_properties( "${LIBNAME}"
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME ${POCO_LIBNAME}
    DEFINE_SYMBOL RemotingNG_EXPORTS
    )

target_link_libraries( "${LIBNAME}" Foundation )
target_include_directories( "${LIBNAME}"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
target_compile_definitions("${LIBNAME}" PUBLIC ${LIB_MODE_DEFINITIONS})

POCO_INSTALL("${LIBNAME}")
POCO_GENERATE_PACKAGE("${LIBNAME}")

