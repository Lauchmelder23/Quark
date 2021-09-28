#include "qkpch.hpp"
#include "Shader.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Quark
{
	namespace Photon
	{
		Shader* Shader::Create(const VertexShaderBinary& vertexSrc, const FragmentShaderBinary& fragmentSrc)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::OpenGL:	return new OpenGLShader(vertexSrc.OpenGL, fragmentSrc.OpenGL);	break;
			default:
				QK_CORE_ASSERT(false, "Photon doesn't support shader creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
				break;
			}

			return nullptr;
		}
	}
}