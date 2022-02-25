#pragma once

#include <glm/glm.hpp>
#include "VertexArray.hpp"

QK_PHOTON_BEGIN
	
	/**
	 * @brief Abstract representation of the underlying rendering API being used (OpenGL, Vulkan, ...)
	 */
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
		/**
		 * @brief Sets the colour the screen should be cleared to
		 * 
		 * @param color RGBA vector representing the color
		 */
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/**
		 * @brief Clears the screen
		 */
		virtual void Clear() = 0;


		/**
		 * @brief Draw call for rendering a VAO with an element buffer
		 * 
		 * @param vertexArray The VAO to render
		 */
		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) = 0;

		/**
		 * @brief Returns the currently used graphics API
		 * 
		 * @return The API currently used by Photon
		 */
		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};

QK_PHOTON_END