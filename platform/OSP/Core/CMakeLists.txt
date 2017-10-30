
find_package(macchina.ioOSP)

add_library(osp.core SHARED src/CoreBundleActivator.cpp)
target_link_libraries(osp.core PocoOSP PocoUtil PocoXML PocoFoundation)
 
create_bundle(TARGET osp.core SPEC_FILE Core.bndlspec)
