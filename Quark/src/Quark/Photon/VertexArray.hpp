#pragma once

#include <memory>

#include "Quark/Core.hpp"
#include "Buffer.hpp"

namespace Quark
{
	namespace Photon
	{
		class QUARK_API VertexArray
		{
		public:
			static VertexArray* Create();

		public:
			virtual ~VertexArray() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
			virtual void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) = 0;
		};
	}
}