#Checking for correct cmake version to suit my needs
cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 20)

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
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Searching for GLM
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glm/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Searching for IMGUI
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/IMGUI/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#Adding subdirectory works when the subdir has a CMakeLists.txt in it
add_subdirectory(glfw)

add_subdirectory(GLAD)

add_subdirectory(glm)

add_subdirectory(IMGUI)
