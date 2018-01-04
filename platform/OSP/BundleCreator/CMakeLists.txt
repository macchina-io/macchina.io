
add_executable(bundle 
    src/BundleCreator.cpp 
    src/ManifestInfo.cpp
)
target_link_libraries(bundle PocoFoundation PocoXML PocoUtil PocoOSP PocoZip)
