#include "qkpch.hpp"
#include "RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Quark
{
	namespace Photon
	{
		RendererAPI* RenderCommand::s_API = new OpenGLRendererAPI;
	}
}