
add_executable(bundle 
    src/BundleCreator.cpp 
    src/ManifestInfo.cpp
)
target_link_libraries(bundle Poco::OSP)

install(TARGETS bundle
  EXPORT OSP
  RUNTIME
    DESTINATION bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
)
