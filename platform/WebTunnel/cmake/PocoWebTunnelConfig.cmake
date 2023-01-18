include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation PocoNet)
include("${CMAKE_CURRENT_LIST_DIR}/PocoWebTunnelTargets.cmake")
