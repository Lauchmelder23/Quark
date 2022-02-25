#include "qkpch.hpp"
#include "OpenGLVertexArray.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>

QK_PHOTON_BEGIN

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

	void OpenGLVertexArray::AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer)
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

	void OpenGLVertexArray::SetElementBuffer(const Reference<ElementBuffer>& elementBuffer)
	{
		glBindVertexArray(m_VertexArray);
		elementBuffer->Bind();

		m_ElementBuffer = elementBuffer;
	}

	const std::vector<Reference<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const Reference<ElementBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_ElementBuffer;
	}

QK_PHOTON_END
