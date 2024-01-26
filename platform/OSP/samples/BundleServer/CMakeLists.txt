# Sources
file(GLOB SAMPLE_SRCS "src/*.cpp")

add_executable(BundleServer ${SAMPLE_SRCS})

target_link_libraries(BundleServer Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation)

add_custom_command(TARGET BundleServer
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/BundleServer.properties ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/any.pem ${CMAKE_BINARY_DIR}
)
