
add_executable(ccutil 
    src/CCUtility.cpp
)
target_link_libraries(ccutil PocoOSP PocoZip PocoUtil PocoXML PocoFoundation)
