# Build used libraries
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/glm)

# Build Quark
add_subdirectory(src)

# ImGui doesn't provide a CMakeLists.txt, so we just build their sources directly into Quark
target_sources(Quark PUBLIC
	"vendor/imgui/imconfig.h"
	"vendor/imgui/imgui.h"
	"vendor/imgui/imgui.cpp"
	"vendor/imgui/imgui_draw.cpp"
	"vendor/imgui/imgui_internal.h"
	"vendor/imgui/imgui_widgets.cpp"
	"vendor/imgui/imstb_rectpack.h"
	"vendor/imgui/imstb_textedit.h"
	"vendor/imgui/imstb_truetype.h"
	"vendor/imgui/imgui_demo.cpp"
	"vendor/imgui/imgui_tables.cpp"
)

target_include_directories(Quark PUBLIC 
	vendor/imgui
)