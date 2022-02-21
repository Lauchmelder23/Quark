#include "qkpch.hpp"
#include "Renderer.hpp"

namespace Quark
{
	namespace Photon
	{
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
	}
}