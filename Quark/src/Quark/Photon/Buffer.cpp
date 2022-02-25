#include "qkpch.hpp"
#include "Buffer.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

QK_PHOTON_BEGIN

	Reference<VertexBuffer>  VertexBuffer::Create(size_t size, float* vertices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexBuffer>(size, vertices);	break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support buffer creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;	// Make VS happy :)
	}

	Reference<ElementBuffer>  ElementBuffer::Create(size_t size, uint32_t* indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLElementBuffer>(size, indices);	break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support buffer creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;	
	}

QK_PHOTON_END