#pragma once

#include "Quark/Core.hpp"

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief Generic abstracted vertex buffer
		 */
		class QUARK_API VertexBuffer
		{
		public:
			/**
			 * @brief          Create a new renderer API specific vertex buffer object
			 * 
			 * @param size     Size of the vertex data in bytes
			 * @param vertices Pointer to the vertex data
			 * @returns        A new renderer APi specific vertex buffer
			 */
			static VertexBuffer* Create(size_t size, float* vertices);

		public:
			virtual ~VertexBuffer() {}

			/**
			 * @brief Bind the vertex buffer
			 */
			virtual void Bind() const = 0;

			/**
			 * @brief Unbind the vertex buffer
			 */
			virtual void Unbind() const = 0;
		};


		/**
		 * @brief Generic abstracted index buffer
		 */
		class QUARK_API IndexBuffer
		{
		public:
			/**
			 * @brief         Create a new renderer API specific element buffer object
			 *
			 * @param count   Number of elements in the index buffer
			 * @param indices Pointer to the index data
			 * @returns       A new renderer API specific index buffer
			 */
			static IndexBuffer* Create(size_t count, uint32_t* indices);

		public:
			virtual ~IndexBuffer() {}

			/**
			 * @brief Bind the vertex buffer
			 */
			virtual void Bind() const = 0;

			/**
			 * @brief Unbind the vertex buffer
			 */
			virtual void Unbind() const = 0;

			/**
			 * @brief Retrieves the number of elements in the buffer
			 * 
			 * @returns Number of elements in the buffer
			 */
			virtual uint32_t GetCount() const = 0;
		};
	}
}