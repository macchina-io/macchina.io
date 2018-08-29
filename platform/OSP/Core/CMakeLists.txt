
find_package(MacchinaOSP)

add_library(osp.core SHARED 
    src/CoreBundleActivator.cpp
)
target_link_libraries(osp.core Poco::OSP)

create_bundle(TARGET osp.core SPEC_FILE Core.bndlspec)
