#include "qkpch.hpp"
#include "Context.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

namespace Quark
{
	namespace Photon
	{
		Context* Context::Create(std::any handle)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::OpenGL:	return new OpenGLContext(std::any_cast<GLFWwindow*>(handle)); break;

			default:
				QK_CORE_ASSERT(false, "Photon doesn't support context creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
				break;
			}
		}
	}
}