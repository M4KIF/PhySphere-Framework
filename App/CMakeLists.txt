#Checking for correct cmake version to suit my needs
cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 20)

add_executable(Voxel-Framework
source.cpp
)

add_library(
	ThreadPool
	"${CMAKE_SOURCE_DIR}/Libraries/thread-pool/BS_thread_pool.hpp"
)

set_target_properties(ThreadPool PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET Voxel-Framework PROPERTY CXX_STANDARD 17)
target_compile_options(Voxel-Framework PRIVATE -Wall)

target_link_libraries(Voxel-Framework PRIVATE glfw)

target_link_libraries(Voxel-Framework PRIVATE glad)

target_link_libraries(Voxel-Framework PRIVATE glm)

target_link_libraries(Voxel-Framework PRIVATE imgui)

target_link_libraries(Voxel-Framework PRIVATE ThreadPool)

target_link_libraries(Voxel-Framework PRIVATE Octree)

target_link_libraries(Voxel-Framework PRIVATE ContainedOctree)

target_link_libraries(Voxel-Framework PRIVATE QuadTree)

target_include_directories(Voxel-Framework PUBLIC "${CMAKE_SOURCE_DIR}/Engine/Collisions")

target_include_directories(Voxel-Framework PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/thread-pool")

target_include_directories(Voxel-Framework PUBLIC "${CMAKE_SOURCE_DIR}/Engine/Spatial-Tree-Structures")
