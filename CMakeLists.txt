#Checking for correct cmake version to suit my needs
cmake_minimum_required(VERSION 3.13)

#Setting the name, compilator flags and c++ version check
project(Voxel-Framework VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 20)

#Linking the "engine libraries" with needed dependencies
add_subdirectory(Libraries)

#Adding Camera as a library
add_library(
	Camera
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Camera/FirstPerson.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Camera/FirstPerson.cpp"
)

#Adding Collisions as a library
add_library(
	Collisions
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Collisions/AABB.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Collisions/AABB.cpp"
)

target_link_libraries(Collisions PRIVATE glm)

#Adding Debug as a library
add_library(
	Debug
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Debug/Log.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Debug/Log.cpp"
)

#Adding Mouse-input as a library
add_library(
	Mouse-input
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Input/Mouse.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Input/Mouse.cpp"
)

#Adding Keyboard-input as a library
add_library(
	Keyboard-input
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Input/Keyboard.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Input/Keyboard.cpp"
)

#Adding Meshing as a library
add_library(
	Meshing
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Meshing/Mesher.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Meshing/Mesher.cpp"
)

#Adding Spatial-Tree-Structures as a library
add_library(
	Octree
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Spatial-Tree-Structures/Octree.h"
)

target_include_directories(Octree PRIVATE "${CMAKE_SOURCE_DIR}/Engine/Collisions")
target_link_libraries(Octree PRIVATE Collisions)

add_library(
	ContainedOctree
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Spatial-Tree-Structures/ContainedOctree.h"
)

target_link_libraries(ContainedOctree PRIVATE Octree)

add_library(
	QuadTree
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Spatial-Tree-Structures/QuadTree.h"
)

target_include_directories(QuadTree PRIVATE "${CMAKE_SOURCE_DIR}/Engine/Collisions")
target_link_libraries(QuadTree PRIVATE Collisions)

add_library(
	ContainedQuadTree
	"${CMAKE_CURRENT_SOURCE_DIR}/Engine/Spatial-Tree-Structures/ContainedQuadTree.h"
)

target_link_libraries(ContainedQuadTree PRIVATE QuadTree)

add_subdirectory(App)
