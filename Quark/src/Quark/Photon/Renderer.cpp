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

		void Renderer::Submit(std::weak_ptr<VertexArray> vertexArray)
		{
			RenderCommand::DrawIndexed(vertexArray);
		}
	}
}