#pragma once

#include "Quark/Photon/Shader.hpp"
#include "Quark/Photon/Datatypes.hpp"

QK_PHOTON_BEGIN

	/**
	* @brief OpenGL specific abstraction of a shader program
	*/
	class QUARK_API OpenGLShader : public Shader
	{
	public:
		/**
		* @brief				Create new OpenGL shader program
		*
		* @param vertexSrc     GLSL source code of the vertex shader
		* @param fragmentSrc	GLSL source code of the fragment shader
		* @returns				A new OpenGL shader program
		*/
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		/** 
		* @brief Delete the shader program
		*/
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_Program;
	};

	/**
	* @brief      Gets the underlying native OpenGL type of a shader datatype
	* 
	* @param type A GLSL datatype
	* @returns	   The underlying OpenGL datatype
	*/
	uint32_t ShaderDataTypeToOpenGLNativeType(ShaderDataType type);

QK_PHOTON_END