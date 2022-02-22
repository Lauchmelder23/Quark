#include "qkpch.hpp"
#include "Buffer.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

QK_PHOTON_BEGIN

	VertexBuffer* VertexBuffer::Create(size_t size, float* vertices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(size, vertices);	break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support buffer creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;	// Make VS happy :)
	}

	ElementBuffer* ElementBuffer::Create(size_t size, uint32_t* indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return new OpenGLElementBuffer(size, indices);	break;

		default:
			QK_CORE_ASSERT(false, "Photon doesn't support buffer creation for the desired render API (id={0})", static_cast<int>(Renderer::GetAPI()));
			break;
		}

		return nullptr;	
	}

QK_PHOTON_END