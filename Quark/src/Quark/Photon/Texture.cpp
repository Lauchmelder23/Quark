#include "qkpch.hpp"
#include "Texture.hpp"

#include <Quark/Photon/Renderer.hpp>
#include <Platform/OpenGL/OpenGLTexture.hpp>

QK_PHOTON_BEGIN

	Reference<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);	break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support Texture creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;
	}

QK_PHOTON_END

