 
find_package(MacchinaOSP)

add_library(Web SHARED
    src/MediaTypeMapper.cpp 
    src/WebServerDispatcher.cpp
    src/WebServerRequestHandlerFactory.cpp
    src/WebServerExtensionPoint.cpp
    src/WebSession.cpp
    src/WebRequestHandlerFactory.cpp
    src/WebServerRequestHandler.cpp
    src/WebSessionManager.cpp
    src/WebServerService.cpp
    src/WebFilter.cpp
    src/WebFilterFactory.cpp
    src/WebFilterExtensionPoint.cpp
)
target_link_libraries(Web  Poco::OSP)
target_include_directories(Web
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src
)
install(DIRECTORY include/ DESTINATION include)

add_library(Poco::OSP::Web ALIAS Web)

add_library(osp.web SHARED 
    src/WebBundleActivator.cpp
)
target_link_libraries(osp.web Poco::OSP::Web)

create_bundle(TARGET osp.web SPEC_FILE WebBundle.bndlspec)

install(TARGETS Web
  EXPORT Web
  LIBRARY
    DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
  PUBLIC_HEADER
    DESTINATION include
)
