#pragma once

#include "Quark/Utility/ShaderBinaryStructs.hpp"

namespace Quark
{
	namespace Photon
	{
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
			static Shader* Create(const VertexShaderBinary& vertexSrc, const FragmentShaderBinary& fragmentSrc);

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
	}
}