project("glad" LANGUAGES C)

add_library(glad STATIC "src/glad.c" "include/glad/glad.h" "include/KHR/khrplatform.h")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

set_property(TARGET glad PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")