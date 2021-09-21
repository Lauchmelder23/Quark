# Build used libraries
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLFW)

set_property(TARGET glfw PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Build Quark
add_subdirectory(src)
target_include_directories(Quark PUBLIC
	"vendor/spdlog/include"
)