# Find packages
find_package(OpenGL REQUIRED)

# Build used libraries
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLFW)

# Explicitly request linkage with the dynamic runtime library
set_property(TARGET spdlog PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set_property(TARGET glfw PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Build Quark
add_subdirectory(src)
target_include_directories(Quark PUBLIC
	${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(Quark PUBLIC 
	${OPENGL_LIBRARIES}
)