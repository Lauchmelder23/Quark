set(QUARK_BUILD_SHARED Off CACHE BOOL "Build a DLL instead of a static library")

set(QUARK_SOURCES 
	"qkpch.cpp"
	"Quark/Log.cpp"
	"Quark/Application.cpp"
 "Platform/Windows/WindowsWindow.cpp" "Quark/Layer.cpp" "Quark/LayerStack.cpp" "Quark/ImGui/ImGuiLayer.cpp"  "Platform/Windows/WindowsInput.cpp" "Quark/ImGui/ImGuiBuild.cpp" "Platform/OpenGL/OpenGLContext.cpp" "Quark/Photon/Shader.cpp" "Quark/Photon/Buffer.cpp" "Platform/OpenGL/OpenGLBuffer.cpp"  "Platform/OpenGL/OpenGLShader.cpp" "Quark/Photon/Context.cpp" "Quark/Photon/VertexArray.cpp" "Platform/OpenGL/OpenGLVertexArray.cpp"  "Quark/Photon/RendererAPI.cpp" "Quark/Photon/Renderer.cpp" "Quark/Photon/RenderCommand.cpp" "Platform/OpenGL/OpenGLRendererAPI.cpp" "Quark/Photon/OrthographicCamera.cpp" "Quark/Photon/Texture.cpp" "Platform/OpenGL/OpenGLTexture.cpp")

if(${QUARK_BUILD_SHARED})
	message(STATUS "Building Quark as a shared library")
	add_library(Quark SHARED
		${QUARK_SOURCES} ${QUARK_HEADERS}
	)

	target_compile_definitions(Quark PUBLIC QK_DYNAMIC_LINK)
else()
	message(STATUS "Building Quark as a static library")
	add_library(Quark STATIC
		${QUARK_SOURCES}
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
	stb
)

if(WIN32)
	target_compile_definitions(Quark PUBLIC
		QK_PLATFORM_WINDOWS 
	)
endif()