#pragma once

#include "Quark/Photon/RendererAPI.hpp"

QK_PHOTON_BEGIN

	class OpenGLRendererAPI :
		public Photon::RendererAPI
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

QK_PHOTON_END