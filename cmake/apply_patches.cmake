# Usage:
# cmake -DPATCH_WORKING_DIRECTORY=.../path/to/project-source -DPATCH_DIR=...path/to/project/patches -P .../path/to/apply_patches.cmake
#
file(GLOB _patchFiles LIST_DIRECTORIES false ${PATCH_DIR}/*)
foreach(_patchFile ${_patchFiles})
    message(STATUS "Applying patch file: ${_patchFile}")
    execute_process(COMMAND patch -p1 INPUT_FILE ${_patchFile} RESULT_VARIABLE _error OUTPUT_VARIABLE _output ERROR_VARIABLE _erroroutput WORKING_DIRECTORY ${PATCH_WORKING_DIRECTORY})
    message(STATUS "${_output}")
    if(_erroroutput)
        message(SEND_ERROR "${_erroroutput}")
    endif()
    if(_error)
        message(FATAL_ERROR "Patch file: ${_patchFile} FAILED!")
    endif()
endforeach()
