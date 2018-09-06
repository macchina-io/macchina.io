
add_executable(ccutil 
    src/CCUtility.cpp
)
target_link_libraries(ccutil Poco::OSP)

#install(TARGETS ccutil
#  EXPORT MaccinaOSP
#  RUNTIME
#    DESTINATION bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
#)
