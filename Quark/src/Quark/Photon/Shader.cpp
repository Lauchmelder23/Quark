#include "qkpch.hpp"
#include "Shader.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

QK_PHOTON_BEGIN
	Reference<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);	break;
		default:
			QK_CORE_ASSERT(false, "Photon doesn't support shader creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;
	}
QK_PHOTON_END