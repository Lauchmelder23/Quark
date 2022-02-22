#pragma once

#include <memory>

#include "Quark/Core.hpp"
#include "Buffer.hpp"

QK_PHOTON_BEGIN

	/**
	* @brief Generic abstracted vertex array object (VAO)
	*/
	class QUARK_API VertexArray
	{
	public:
		/**
		* @brief          Create a new renderer API specific VAO
		*
		* @returns        A new renderer API specific VAO
		*/
		static VertexArray* Create();

	public:
		virtual ~VertexArray() {}

		/**
		* @brief Bind the VAO
		*/
		virtual void Bind() const = 0;

		/**
		* @brief Unind the VAO
		*/
		virtual void Unbind() const = 0;

		/**
		* @brief              Add a new VBO to the VAO
		* 
		* @param vertexBuffer A VBO with the layout already set 
		*/
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

		/**
		* @brief              Add a new EBO to the VAO
		*
		* @param vertexBuffer The EBO to set in the VAO
		*/
		virtual void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<ElementBuffer>& GetIndexBuffer() const = 0;
	};

QK_PHOTON_END