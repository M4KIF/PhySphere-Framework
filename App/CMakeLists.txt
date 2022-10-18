#Checking for correct cmake version to suit my needs
cmake_minimum_required(VERSION 3.13)

add_executable(Voxel-Framework
source.cpp
)

set_property(TARGET Voxel-Framework PROPERTY CXX_STANDARD 17)
target_compile_options(Voxel-Framework PRIVATE -Wall)

target_link_libraries(Voxel-Framework PRIVATE glfw)

target_link_libraries(Voxel-Framework PRIVATE glad)

target_link_libraries(Voxel-Framework PRIVATE glm)

target_link_libraries(Voxel-Framework PRIVATE imgui)

target_link_libraries(Voxel-Framework PRIVATE QuadTree)

target_link_libraries(Voxel-Framework PRIVATE Octree)
