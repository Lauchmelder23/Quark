#pragma once

#include "Quark/Core.hpp"
#include "Quark/Photon/VertexArray.hpp"

QK_PHOTON_BEGIN

	/**
	* @brief OpenGL specific abstraction of a VAO
	*/
	class QUARK_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		/**
		 * @copydoc VertexArray::Bind()
		 */
		void Bind() const override;

		/**
		 * @copydoc VertexArray::Unbind()
		 */
		void Unbind() const override;


		/**
		 * @copydoc VertexArray::AddVertexBuffer()
		 */
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		
		/**
		 * @copydoc VertexArray::SetElementBuffer()
		 */
		void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) override;


		/**
		 * @copydoc VertexArray::GetVertexBuffers()
		 */
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;

		/**
		 * @copydoc VertexArray::GetIndexBuffer()
		 */
		virtual const std::shared_ptr<ElementBuffer>& GetIndexBuffer() const override;

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<ElementBuffer> m_ElementBuffer;

		uint32_t m_VertexArray;
	};

QK_PHOTON_END
