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

		OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, float* vertices) :
			m_Layout{}
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

		OpenGLElementBuffer::OpenGLElementBuffer(size_t count, uint32_t* indices) :
			m_Count(count)
		{
			glCreateBuffers(1, &m_ElementBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (void*)indices, GL_STATIC_DRAW);
		}

		OpenGLElementBuffer::~OpenGLElementBuffer()
		{
			glDeleteBuffers(1, &m_ElementBuffer);
		}

		void OpenGLElementBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
		}

		void OpenGLElementBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
