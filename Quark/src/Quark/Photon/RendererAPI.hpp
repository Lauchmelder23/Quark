#pragma once

#include <glm/glm.hpp>
#include "VertexArray.hpp"

namespace Quark
{
	namespace Photon
	{
		class RendererAPI
		{
		public:
			/**
			 * @brief Render APIs supported by Photon
			 */
			enum class API
			{
				None = -1,
				OpenGL
			};

		public:
			virtual void SetClearColor(const glm::vec4& color) = 0;
			virtual void Clear() = 0;

			virtual void DrawIndexed(std::weak_ptr<VertexArray> vertexArray) = 0;


			inline static API GetAPI() { return s_API; }
		private:
			static API s_API;
		};
	}
}