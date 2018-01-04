
find_package(MacchinaOSP)
 
add_library(com.appinf.osp.samples.servicelistener SHARED src/ServiceListener.cpp)
target_include_directories(com.appinf.osp.samples.servicelistener PUBLIC include)
target_link_libraries(com.appinf.osp.samples.servicelistener PocoOSP PocoNet PocoUtil PocoXML PocoFoundation)
 
create_bundle(TARGET com.appinf.osp.samples.servicelistener SPEC_FILE ServiceListener.bndlspec)
