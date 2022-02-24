#pragma once

#include <glm/glm.hpp>

QK_PHOTON_BEGIN

	/**
	* @brief Generic abstracted shader program
	*/
	class QUARK_API Shader
	{
	public:
		/**
		* @brief				Create a new renderer API specific shader program
		*
		* @param vertexSrc		Structure containing generic vertex shader data
		* @param fragmentSrc	Structure containing generic fragment shader data
		* @returns				A new renderer API specific shader program
		*/
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	public:
		virtual ~Shader() {}

		/**
		* @brief Bind the shader program
		*/
		virtual void Bind() const = 0;

		/**
		* @brief Unind the shader program
		*/
		virtual void Unbind() const = 0;
	};

QK_PHOTON_END