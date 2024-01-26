# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

# Version Resource
if(MSVC)
	source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
	list(APPEND SRCS ${PROJECT_SOURCE_DIR}/ProDLLVersion.rc)
endif()

add_executable(RemoteGenNG ${SRCS})
set_target_properties(RemoteGenNG
	PROPERTIES
	OUTPUT_NAME RemoteGenNG
)

target_link_libraries(RemoteGenNG PUBLIC Poco::Foundation Poco::Util Poco::RemotingNG Poco::CodeGeneration Poco::CppParser)

install(
	TARGETS RemoteGenNG EXPORT "RemoteGenNG"
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
