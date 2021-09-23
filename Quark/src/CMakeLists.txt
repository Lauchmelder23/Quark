set(QUARK_SOURCES 
	"qkpch.cpp"
	"Quark/Log.cpp"
	"Quark/Application.cpp"
 "Platform/Windows/WindowsWindow.cpp" "Quark/Layer.cpp" "Quark/LayerStack.cpp" "Quark/ImGui/ImGuiLayer.cpp" "Platform/OpenGL/ImGuiOpenGLRenderer.cpp" "Platform/Windows/WindowsInput.cpp")

set(QUARK_HEADERS
	"Quark.hpp"
	"Quark/Log.hpp"
	"Quark/EntryPoint.hpp"
	"Quark/Core.hpp"
	"Quark/Application.hpp"
	"Quark/Events/Event.hpp"
	"Quark/Events/ApplicationEvent.hpp"
	"Quark/Events/KeyEvent.hpp"
	"Quark/Events/MouseEvent.hpp"
	"Quark/Window.hpp"
  "Platform/Windows/WindowsWindow.hpp" "Quark/Layer.hpp" "Quark/LayerStack.hpp" "Quark/ImGui/ImGuiLayer.hpp" "Platform/OpenGL/ImGuiOpenGLRenderer.hpp" "Quark/Input.hpp" "Platform/Windows/WindowsInput.hpp")

add_library(Quark SHARED 
	${QUARK_SOURCES} ${QUARK_HEADERS}
)

target_include_directories(Quark PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(Quark PUBLIC 
	spdlog
	glfw
	glad
	${OPENGL_LIBRARIES}
)

if(WIN32)
	target_compile_definitions(Quark PUBLIC
		QK_PLATFORM_WINDOWS 
	)
	target_compile_definitions(Quark PRIVATE 
		QK_BUILD_DLL
	)
endif()

set_property(TARGET Quark PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")