cmake_minimum_required(VERSION 3.16)

project(Quark LANGUAGES CXX)
set(CMAKE_CXX_VERSION 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQK_ENABLE_ASSERTS -DGLFW_INCLUDE_NONE")

add_subdirectory(Quark)
add_subdirectory(Sandbox)