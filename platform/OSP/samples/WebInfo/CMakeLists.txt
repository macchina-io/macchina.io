
find_package(MacchinaOSP)
 
add_library(com.appinf.osp.samples.webinfo SHARED 
    src/WebInfo.cpp
)
target_include_directories(com.appinf.osp.samples.webinfo PUBLIC include)
target_link_libraries(com.appinf.osp.samples.webinfo PocoOSPWeb PocoOSP PocoNet PocoUtil PocoXML PocoFoundation)
 
create_bundle(TARGET com.appinf.osp.samples.webinfo SPEC_FILE WebInfo.bndlspec)
