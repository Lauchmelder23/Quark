#pragma once

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief Render APIs supported by Photon
		 */
		enum class RendererAPI
		{
			None = -1,
			OpenGL,
			Vulkan
		};

		/**
		 * @brief Renderer structure for doing/storing generic render API actions/data
		 */
		class Renderer
		{
		private:
			inline static RendererAPI s_RendererAPI = RendererAPI::None;

		public:
			/**
			 * @brief   Retrieve the currently used renderer API
			 * 
			 * @returns The current active API
			 */
			inline static RendererAPI GetAPI() { return s_RendererAPI; };

			/**
			 * @brief     Set the renderer API that should be used across the application
			 *
			 * @param api The new API
			 */
			inline static void SetAPI(RendererAPI api) { s_RendererAPI = api; }
		};
	}
}