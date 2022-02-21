#include "qkpch.hpp"
#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void OpenGLRendererAPI::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::DrawIndexed(std::weak_ptr<VertexArray> vertexArray)
		{
			const std::shared_ptr<VertexArray> obj = vertexArray.lock();
			glDrawElements(GL_TRIANGLES, obj->GetIndexBuffer().lock()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}


