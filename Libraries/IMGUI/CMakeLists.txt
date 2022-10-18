cmake_minimum_required(VERSION 3.0)
project(Imgui)

add_library(imgui "${PROJECT_SOURCE_DIR}/imgui/imgui.h" "${PROJECT_SOURCE_DIR}/imgui/imgui.cpp")
target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR/imgui}")
