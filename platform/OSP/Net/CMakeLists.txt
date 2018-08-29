 
find_package(MacchinaOSP)
 
add_library(poco.net SHARED 
    src/NetBundleActivator.cpp
)
target_link_libraries(poco.net Poco::OSP)

create_bundle(TARGET poco.net SPEC_FILE Net.bndlspec)
