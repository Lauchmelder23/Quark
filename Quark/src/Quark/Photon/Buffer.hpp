#pragma once

#include "Quark/Core.hpp"
#include "Datatypes.hpp"

namespace Quark
{
	namespace Photon
	{

		/**
		 * @brief Represents a single element in a buffer
		 * 
		 * Buffers sent to the GPU have no default layout, the application can
		 * store data in any way it wants in the buffers, as long as it describes
		 * how that data is laid out (see BufferLayout). This structure represents
		 * one type of data in such a buffer
		 */
		struct BufferElement
		{
			std::string Name;
			ShaderDataType Type;
			uint32_t Size;
			uint32_t Offset;
			bool Normalized;

			BufferElement(ShaderDataType type, const std::string& name) :
				Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(false) 
			{
			}
		};

		/**
		 * @brief Data structure for holding information about buffer layouts
		 * 
		 * In order to send data to a shader, the renderer API needs to have information
		 * about how the data is laid out in the buffer. Since this layout information is
		 * implementation specific, this class provides a uniform API to handle the deifferences
		 */
		class BufferLayout
		{
		public:
			BufferLayout(const std::initializer_list<BufferElement>& elements) :
				m_Elements(elements) 
			{
				CalculateOffsetsAndStride();
			}

			inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
			inline uint32_t GetStride() const { return m_Stride; }

			std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		private:
			void CalculateOffsetsAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;
				for (BufferElement& element : m_Elements)
				{
					element.Offset = m_Stride;
					m_Stride += element.Size;
				}
			}

		private:
			std::vector<BufferElement> m_Elements;
			uint32_t m_Stride;
		};


		/**
		 * @brief Generic abstracted vertex buffer object (VBO)
		 */
		class QUARK_API VertexBuffer
		{
		public:
			/**
			 * @brief          Create a new renderer API specific VBO
			 * 
			 * @param size     Size of the vertex data in bytes
			 * @param vertices Pointer to the vertex data
			 * @returns        A new renderer APi specific VBO
			 */
			static VertexBuffer* Create(size_t size, float* vertices);

		public:
			virtual ~VertexBuffer() {}

			/**
			 * @brief Bind the VBO
			 */
			virtual void Bind() const = 0;

			/**
			 * @brief Unbind the VBO
			 */
			virtual void Unbind() const = 0;

			/**
			 * @brief        Defines the VBO's layout
			 * 
			 * @param layout A BufferLayout describing the layout
			 */
			virtual void SetLayout(const BufferLayout& layout) = 0;

			/**
			 * @brief   Retrieves the VBO's layout
			 *
			 * @returns The buffers layout
			 */
			virtual const BufferLayout& GetLayout() const = 0;
		};


		/**
		 * @brief Generic abstracted element buffer object (EBO)
		 */
		class QUARK_API ElementBuffer
		{
		public:
			/**
			 * @brief          Create a new renderer API specific EBO
			 *
			 * @param count    Number of elements in the EBO
			 * @param elements Pointer to the index data
			 * @returns        A new renderer API specific EBO
			 */
			static ElementBuffer* Create(size_t count, uint32_t* elements);

		public:
			virtual ~ElementBuffer() {}

			/**
			 * @brief Bind the EBO
			 */
			virtual void Bind() const = 0;

			/**
			 * @brief Unbind the EBO
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