#include "qkpch.hpp"
#include "Context.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

QK_PHOTON_BEGIN

	Context* Context::Create(std::any handle)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return new OpenGLContext(std::any_cast<GLFWwindow*>(handle)); break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support context creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}
	}

QK_PHOTON_END