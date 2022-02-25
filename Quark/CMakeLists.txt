# Build used libraries
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/stb)

# ImGui doesn't provide a CMakeLists.txt, so we have to build it ourselves
add_library(ImGui
	"vendor/imgui/imgui.cpp"
	"vendor/imgui/imgui_draw.cpp"
	"vendor/imgui/imgui_widgets.cpp"
	"vendor/imgui/imgui_demo.cpp"
	"vendor/imgui/imgui_tables.cpp"
)

target_include_directories(ImGui PUBLIC
	"vendor/imgui"
)

# Build Quark
add_subdirectory(src)

target_link_libraries(Quark PUBLIC 
	ImGui
)