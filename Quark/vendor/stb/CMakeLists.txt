project(stb LANGUAGES C)

add_library(stb STATIC "src/stb.c")
target_include_directories(stb PUBLIC "include")

set_property(TARGET stb PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")