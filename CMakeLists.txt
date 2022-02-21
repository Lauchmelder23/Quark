cmake_minimum_required(VERSION 3.16)

project(Quark LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQK_ENABLE_ASSERTS -DGLFW_INCLUDE_NONE")

option(BUILD_EXAMPLE "Build Example Project")

add_subdirectory(Quark)

if(${BUILD_EXAMPLE})
	add_subdirectory(Sandbox)
endif()