#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.hpp"

namespace Quark
{
	namespace Photon
	{
		class RenderCommand
		{
		public:
			inline static void SetClearColor(const glm::vec4& color)
			{
				s_API->SetClearColor(color);
			}

			inline static void Clear()
			{
				s_API->Clear();
			}

			inline static void DrawIndexed(std::weak_ptr<VertexArray> vertexArray)
			{
				s_API->DrawIndexed(vertexArray);
			}

		private:
			static RendererAPI* s_API;
		};
	}
}