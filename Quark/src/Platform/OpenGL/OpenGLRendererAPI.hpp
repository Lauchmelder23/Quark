#pragma once

#include "Quark/Photon/RendererAPI.hpp"

namespace Quark
{
	namespace Photon
	{
		class OpenGLRendererAPI :
			public Photon::RendererAPI
		{
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(std::weak_ptr<VertexArray> vertexArray) override;
		};
	}
}