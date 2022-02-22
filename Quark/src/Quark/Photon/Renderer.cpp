#include "qkpch.hpp"
#include "Renderer.hpp"

QK_PHOTON_BEGIN

	void Renderer::BeginScene()
	{
		// Does nothing right now
	}

	void Renderer::EndScene()
	{
		// Does nothing right now
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

QK_PHOTON_END