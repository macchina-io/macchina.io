 
find_package(MacchinaOSP)

add_library(PocoOSPWeb SHARED 
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
target_link_libraries(PocoOSPWeb  Poco::OSP)
target_include_directories(PocoOSPWeb
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src
)
install(DIRECTORY include/ DESTINATION include)

add_library(Poco::OSP::Web ALIAS PocoOSPWeb)

add_library(osp.web SHARED 
    src/WebBundleActivator.cpp
)
target_link_libraries(osp.web Poco::OSP::Web)

create_bundle(TARGET osp.web SPEC_FILE WebBundle.bndlspec)

install(TARGETS PocoOSPWeb
  EXPORT Web
  LIBRARY
    DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
  PUBLIC_HEADER
    DESTINATION include
)
