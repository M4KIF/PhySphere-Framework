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

add_library(
	ContainedOctree 
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree/ContainedOctree.h"
)

#Adding the Octree library
add_library(
	Octree 
	"${CMAKE_SOURCE_DIR}/Libraries/Spatial-Tree-Structures/Octree/Octree.h"
)

set_target_properties(ContainedOctree  PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Octree PROPERTIES LINKER_LANGUAGE CXX)

#Giving the path to the needed includes
target_include_directories(ContainedOctree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Octree")
target_include_directories(Octree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Octree")

target_link_libraries(Octree PUBLIC glm)

target_link_libraries(ContainedOctree PUBLIC Octree)
