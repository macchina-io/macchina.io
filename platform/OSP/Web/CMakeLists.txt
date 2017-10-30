 
find_package(macchina.ioOSP)

set(BUNDLE_LIBRARY 
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

add_library(PocoOSPWeb SHARED ${BUNDLE_LIBRARY})
target_link_libraries(PocoOSPWeb  PocoOSP PocoNet PocoUtil PocoXML PocoFoundation)
target_include_directories(PocoOSPWeb PUBLIC include)

add_library(osp.web SHARED src/WebBundleActivator.cpp)
target_link_libraries(osp.web PocoOSPWeb)
 
create_bundle(TARGET osp.web SPEC_FILE WebBundle.bndlspec)
