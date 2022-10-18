#Checking for correct cmake version to suit my needs
cmake_minimum_required(VERSION 3.13)

#Setting the name, compilator flags and c++ version check
project(Voxel-Framework VERSION 1.0.0)

#Checking for git submodules updates, via checking the .gitmodules file and
#pulling the modules that are written in it.
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#Searching for GLFW
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Searching for GLM
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/glm/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Searching for IMGUI
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/IMGUI/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Adding subdirectory works when the subdir has a CMakeLists.txt in it
include_directories(Libraries)

add_subdirectory(Libraries/glfw)

add_subdirectory(Libraries/GLAD)

add_subdirectory(Libraries/glm)

add_subdirectory(Libraries/IMGUI)

#Adding the Octree library
add_library(
	ContainedOctree 
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree/ContainedOctree.h"
)

add_library(
	Octree 
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree/Octree.h"
)

#Setting the language to cxx because the libs only contain headers
set_target_properties(ContainedOctree  PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Octree PROPERTIES LINKER_LANGUAGE CXX)

#Giving the path to the needed includes
target_include_directories(ContainedOctree PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree")
target_include_directories(Octree PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree")

target_link_libraries(Octree PUBLIC glm)

target_link_libraries(ContainedOctree PUBLIC Octree)

#Adding the quadtree as a library
add_library(
	ContainedQuadTree
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/QuadTree/ContainedQuadTree.h"
)

#Adding the Octree library
add_library(
	QuadTree 
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/QuadTree/QuadTree.h"
)

#Setting the language to cxx because the libs only contain headers
set_target_properties(ContainedQuadTree  PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(QuadTree PROPERTIES LINKER_LANGUAGE CXX)

#Giving the path to the needed includes
target_include_directories(ContainedQuadTree PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/QuadTree/")
target_include_directories(QuadTree PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/QuadTree/")

target_link_libraries(QuadTree PUBLIC glm)

target_link_libraries(ContainedQuadTree PUBLIC Octree)

include_directories(Libraries)

add_subdirectory(App)
