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

		/**
		 * @copydoc Shader::Bind()
		 */
		virtual void Bind() const override;

		/**
		 * @copydoc Shader::Unbind()
		 */
		virtual void Unbind() const override;


		/**
		 * @brief Uploads an int to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param vec Data to be uploaded
		 */
		void SetUniformInt(const std::string& name, int vec);


		/**
		 * @brief Uploads a float to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param vec Data to be uploaded
		 */
		void SetUniformFloat(const std::string& name, float vec);

		/**
		* @brief Uploads a vec2 to the current bound shader
		*
		* @param name Name of the uniform to upload
		* @param vec Data to be uploaded
		*/
		void SetUniformFloat2(const std::string& name, const glm::vec2& vec);

		/**
		 * @brief Uploads a vec3 to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param vec Data to be uploaded
		 */
		void SetUniformFloat3(const std::string& name, const glm::vec3& vec);


		/**
		 * @brief Uploads a vec4 to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param vec Data to be uploaded
		 */
		void SetUniformFloat4(const std::string& name, const glm::vec4& vec);


		/**
		 * @brief Uploads a 3x3 matrix to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param matrix Data to be uploaded°
		 */
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);


		/**
		 * @brief Uploads a 4x4 matrix to the current bound shader
		 *
		 * @param name Name of the uniform to upload
		 * @param matrix Data to be uploaded°
		 */
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);


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