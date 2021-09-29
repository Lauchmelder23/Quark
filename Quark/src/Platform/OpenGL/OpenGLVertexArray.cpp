#include "qkpch.hpp"
#include "OpenGLVertexArray.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		OpenGLVertexArray::OpenGLVertexArray()
		{
			glCreateVertexArrays(1, &m_VertexArray);
		}

		OpenGLVertexArray::~OpenGLVertexArray()
		{
		}

		void OpenGLVertexArray::Bind() const
		{
			glBindVertexArray(m_VertexArray);
		}

		void OpenGLVertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			glBindVertexArray(m_VertexArray);
			vertexBuffer->Bind();

			uint32_t index = 0;
			const BufferLayout& layout = vertexBuffer->GetLayout();
			for (const BufferElement& element : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					ShaderDataTypeCount(element.Type),
					ShaderDataTypeToOpenGLNativeType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(void*)element.Offset
				);

				index++;
			}

			m_VertexBuffers.push_back(vertexBuffer);
		}

		void OpenGLVertexArray::SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer)
		{
			glBindVertexArray(m_VertexArray);
			elementBuffer->Bind();

			m_ElementBuffer = elementBuffer;
		}
	}
}