#pragma once 

#include "Quark/Core.hpp"
#include "Quark/Photon/Buffer.hpp"

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief OpenGL specific abstraction of a vertex buffer object
		 */
		class QUARK_API OpenGLVertexBuffer : public VertexBuffer
		{
		public:
			/**
			 * @brief Create new OpenGL VBO
			 * 
			 * @param size     Size of the vertex data in bytes
			 * @param vertices Pointer to the vertex data
			 * @returns        A new OpenGL vertex buffer
			 */
			OpenGLVertexBuffer(size_t size, float* vertices);

			/**
			 * @brief Delete the VBO
			 */
			virtual ~OpenGLVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

		private:
			uint32_t m_VertexBuffer;
		};


		/**
		 * @brief OpenGL specific abstraction of an index buffer
		 */
		class QUARK_API OpenGLIndexBuffer : public IndexBuffer
		{
		public:
			/**
			 * @brief Create new OpenGL index buffer
			 *
			 * @param count   Number of elements in the index buffer
			 * @param indices Pointer to the index data
			 * @returns       A new renderer OpenGL index buffer
			 */
			OpenGLIndexBuffer(size_t count, uint32_t* indices);

			/**
			 * @brief Delete the index buffer
			 */
			virtual ~OpenGLIndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual uint32_t GetCount() const override { return m_Count; };

		private:
			uint32_t m_IndexBuffer;
			uint32_t m_Count;
		};
	}
}