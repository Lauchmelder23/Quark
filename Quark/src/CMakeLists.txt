set(QUARK_BUILD_SHARED Off CACHE BOOL "Build a DLL instead of a stati library")

set(QUARK_SOURCES 
	"qkpch.cpp"
	"Quark/Log.cpp"
	"Quark/Application.cpp"
 "Platform/Windows/WindowsWindow.cpp" "Quark/Layer.cpp" "Quark/LayerStack.cpp" "Quark/ImGui/ImGuiLayer.cpp"  "Platform/Windows/WindowsInput.cpp" "Quark/MouseButtonCodes.hpp")

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
  "Platform/Windows/WindowsWindow.hpp" "Quark/Layer.hpp" "Quark/LayerStack.hpp" "Quark/ImGui/ImGuiLayer.hpp"  "Quark/Input.hpp" "Platform/Windows/WindowsInput.hpp" "Quark/KeyCodes.hpp" "Quark/Utility/Bimap.hpp" "Quark/ImGui/ImGuiBuild.cpp")

if(${QUARK_BUILD_SHARED})
	message(STATUS "Building Quark as a shared library")
	add_library(Quark SHARED
		${QUARK_SOURCES} ${QUARK_HEADERS}
	)

	target_compile_definitions(Quark PUBLIC QK_DYNAMIC_LINK)
else()
	message(STATUS "Building Quark as a static library")
	add_library(Quark STATIC
		${QUARK_SOURCES} ${QUARK_HEADERS}
	)
	
	set_property(TARGET spdlog PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET glfw PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET Quark PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET ImGui PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_include_directories(Quark PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Quark PUBLIC 
	spdlog
	glfw
	glad
	glm
)

if(WIN32)
	target_compile_definitions(Quark PUBLIC
		QK_PLATFORM_WINDOWS 
	)
endif()