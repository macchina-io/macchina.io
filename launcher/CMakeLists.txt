
add_executable(macchina-launcher src/MacchinaLauncher.cpp)

target_link_libraries(macchina-launcher Poco::Util Poco::JSON Poco::XML)
