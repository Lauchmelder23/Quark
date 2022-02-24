#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.hpp"

QK_PHOTON_BEGIN
	
	/**
	 * @brief Represents arbitrary, implementation agnostic rendering commands
	 */
	class RenderCommand
	{
	public:
		/**
		 * @copydoc RendererAPI::SetClearColor()
		 */
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_API->SetClearColor(color);
		}

		/**
		 * @copydoc RendererAPI::Clear()
		 */
		inline static void Clear()
		{
			s_API->Clear();
		}

		/**
		 * @copydoc RendererAPI::DrawIndexed()
		 */
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_API->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_API;
	};

QK_PHOTON_END