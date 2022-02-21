#pragma once

#include "Quark/Core.hpp"
#include "Quark/Photon/VertexArray.hpp"

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief OpenGL specific abstraction of a VAO
		 */
		class QUARK_API OpenGLVertexArray : public VertexArray
		{
		public:
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();

			void Bind() const override;
			void Unbind() const override;

			void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
			void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) override;

			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
			virtual const std::weak_ptr<ElementBuffer> GetIndexBuffer() const override;

		private:
			std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
			std::shared_ptr<ElementBuffer> m_ElementBuffer;

			uint32_t m_VertexArray;
		};
	}
}