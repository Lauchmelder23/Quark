#include "qkpch.hpp"
#include "VertexArray.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Quark
{
	namespace Photon
	{
		VertexArray* VertexArray::Create()
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();	break;

			default:
				QK_CORE_ASSERT(false, "Photon doesn't support VAO creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
				break;
			}

			return nullptr;
		}
	}
}