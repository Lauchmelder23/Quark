#include "qkpch.hpp"
#include "OpenGLBuffer.hpp"

#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		//////////////////////////////////////////////////
		////          OPENGL VERTEX BUFFERS            ///
		//////////////////////////////////////////////////

		OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, float* vertices)
		{
			glCreateBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, size, (void*)vertices, GL_STATIC_DRAW);
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{
			glDeleteBuffers(1, &m_VertexBuffer);
		}

		void OpenGLVertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		}

		void OpenGLVertexBuffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		//////////////////////////////////////////////////
		////           OPENGL INDEX BUFFERS            ///
		//////////////////////////////////////////////////

		OpenGLIndexBuffer::OpenGLIndexBuffer(size_t count, uint32_t* indices) :
			m_Count(count)
		{
			glCreateBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (void*)indices, GL_STATIC_DRAW);
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{
			glDeleteBuffers(1, &m_IndexBuffer);
		}

		void OpenGLIndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		}

		void OpenGLIndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
