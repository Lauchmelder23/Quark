#pragma once

#include "Quark/Photon/RendererAPI.hpp"

QK_PHOTON_BEGIN

	/**
	 * @brief Abstraction of the OpenGL Graphics API
	 */
	class OpenGLRendererAPI :
		public RendererAPI
	{
	public:
		/**
		 * @copydoc RendererAPI::Init()
		 */
		virtual void Init() override;

		/**
		 * @copydoc RendererAPI::SetClearColor()
		 */
		virtual void SetClearColor(const glm::vec4& color) override;

		/**
		 * @copydoc RendererAPI::Clear()
		 */
		virtual void Clear() override;


		/**
		 * @copydoc RendererAPI::DrawIndexed()
		 */
		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) override;
	};

QK_PHOTON_END