#pragma once

#include "Quark/Core.hpp"

namespace Quark
{
	namespace Photon
	{
		/**
		 * An enum representing every possible datatype common in shading languages
		 */
		enum class ShaderDataType
		{
			None = -1,
			Bool, Bool2, Bool3, Bool4,
			Int, Int2, Int3, Int4,
			Uint, Uint2, Uint3, Uint4,
			Float, Float2, Float3, Float4,
			Double, Double2, Double3, Double4,

			Mat2x2, Mat2x3, Mat2x4, 
			Mat3x2, Mat3x3, Mat3x4, 
			Mat4x2, Mat4x3, Mat4x4, 

			Mat2 = Mat2x2,
			Mat3 = Mat3x3,
			Mat4 = Mat4x4
		};

		/**
		 * @brief      Calculates the size of a shader datatype
		 * 
		 * @param type The datatype to calculate the size of
		 * @return     The size of the datatype
		 */
		static size_t ShaderDatatTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Bool:		return 4 * 1;
			case ShaderDataType::Bool2:		return 4 * 2;
			case ShaderDataType::Bool3:		return 4 * 3;
			case ShaderDataType::Bool4:		return 4 * 4;

			case ShaderDataType::Int:		return 4 * 1;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;

			case ShaderDataType::Uint:		return 4 * 1;
			case ShaderDataType::Uint2:		return 4 * 2;
			case ShaderDataType::Uint3:		return 4 * 3;
			case ShaderDataType::Uint4:		return 4 * 4;

			case ShaderDataType::Float:		return 4 * 1;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;

			case ShaderDataType::Double:	return 8 * 1;
			case ShaderDataType::Double2:	return 8 * 2;
			case ShaderDataType::Double3:	return 8 * 3;
			case ShaderDataType::Double4:	return 8 * 4;

			case ShaderDataType::Mat2x2:	return 4 * 2 * 2;
			case ShaderDataType::Mat2x3:	return 4 * 2 * 3;
			case ShaderDataType::Mat2x4:	return 4 * 2 * 4;

			case ShaderDataType::Mat3x2:	return 4 * 3 * 2;
			case ShaderDataType::Mat3x3:	return 4 * 3 * 3;
			case ShaderDataType::Mat3x4:	return 4 * 3 * 4;

			case ShaderDataType::Mat4x2:	return 4 * 4 * 2;
			case ShaderDataType::Mat4x3:	return 4 * 4 * 3;
			case ShaderDataType::Mat4x4:	return 4 * 4 * 4;
			}

			QK_CORE_ASSERT(false, "Unknown shader datatype");
		}

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

			BufferElement(ShaderDataType type, const std::string& name) :
				Name(name), Type(type), Size(ShaderDatatTypeSize(type)), Offset(0)
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
			friend class VertexBuffer;

		public:
			BufferLayout(const std::initializer_list<BufferElement>& elements) :
				m_Elements(elements) 
			{
				CalculateOffsetsAndStride();
			}

			inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

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

			/**
			 * @brief        Defines the vertex buffers layout
			 * 
			 * @param layout A BufferLayout describing the layout
			 */
			virtual void SetLayout(const BufferLayout& layout) = 0;

			/**
			 * @brief   Retrieves the vertex buffers layout
			 *
			 * @returns The buffers layout
			 */
			virtual const BufferLayout& GetLayout() const = 0;
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