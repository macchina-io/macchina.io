# Sources
file(GLOB SRCS_G "src/*.cpp")
list(REMOVE_ITEM SRCS_G "${CMAKE_CURRENT_SOURCE_DIR}/src/TestBundle.cpp")
POCO_SOURCES_AUTO(TEST_SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "src/*.h")
POCO_HEADERS_AUTO(TEST_SRCS ${HDRS_G})

POCO_SOURCES_AUTO_PLAT(TEST_SRCS OFF
	src/WinDriver.cpp
)

add_executable(OSP-testrunner ${TEST_SRCS})
if(ANDROID)
	add_test(
		NAME OSP
		WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
		COMMAND ${CMAKE_COMMAND} -DANDROID_NDK=${ANDROID_NDK} -DLIBRARY_DIR=${CMAKE_BINARY_DIR}/lib -DUNITTEST=${CMAKE_BINARY_DIR}/bin/OSP-testrunner -DTEST_PARAMETER=-all -P ${CMAKE_SOURCE_DIR}/cmake/ExecuteOnAndroid.cmake
	)
else()
	add_test(
		NAME OSP
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND OSP-testrunner -ignore ${CMAKE_SOURCE_DIR}/cppignore.lnx -all
	)
	set_tests_properties(OSP PROPERTIES ENVIRONMENT POCO_BASE=${CMAKE_SOURCE_DIR})
endif()

target_link_libraries(OSP-testrunner Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation CppUnit)
target_include_directories(OSP-testrunner
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(TestBundle MODULE src/TestBundle.cpp)
set_target_properties(TestBundle
	PROPERTIES
	PREFIX ""
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set_target_properties(TestBundle PROPERTIES SUFFIX ".dylib")
endif()

target_link_libraries(TestBundle Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation)

add_custom_command(TARGET TestBundle
	POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/bundles
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/bundles ${CMAKE_CURRENT_BINARY_DIR}/bundles
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/bundles/com.appinf.osp.bundle9_1.0.0/bin/${OSP_OSNAME}/${OSP_OSARCH}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestBundle> ${CMAKE_CURRENT_BINARY_DIR}/bundles/com.appinf.osp.bundle9_1.0.0/bin/${OSP_OSNAME}/${OSP_OSARCH}
)
