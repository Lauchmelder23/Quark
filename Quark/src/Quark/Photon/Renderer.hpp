#pragma once

#include "RenderCommand.hpp"

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief Renderer structure for doing/storing generic render API actions/data
		 */
		class Renderer
		{
		public:
			static void BeginScene();
			static void EndScene();

			static void Submit(std::weak_ptr<VertexArray> vertexArray);

		public:
			/**
			 * @brief   Retrieve the currently used renderer API
			 * 
			 * @returns The current active API
			 */
			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
		};
	}
}