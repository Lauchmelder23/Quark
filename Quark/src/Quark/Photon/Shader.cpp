#include "qkpch.hpp"
#include "Shader.hpp"

#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) :
			m_ProgramID(0)
		{
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			const GLchar* src = static_cast<const GLchar*>(vertexSrc.c_str());
			glShaderSource(vertexShader, 1, &src, nullptr);
			glCompileShader(vertexShader);

			GLint isCompiled = 0;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());

				glDeleteShader(vertexShader);

				throw std::runtime_error(infoLog.data());
			}

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			src = static_cast<const GLchar*>(fragmentSrc.c_str());
			glShaderSource(fragmentShader, 1, &src, 0);
			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());

				glDeleteShader(fragmentShader);
				glDeleteShader(vertexShader);

				throw std::runtime_error(infoLog.data());
			}

			m_ProgramID = glCreateProgram();
			glAttachShader(m_ProgramID, vertexShader);
			glAttachShader(m_ProgramID, fragmentShader);
			glLinkProgram(m_ProgramID);

			GLint isLinked = 0;
			glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, infoLog.data());

				glDeleteProgram(m_ProgramID);
				glDeleteShader(fragmentShader);
				glDeleteShader(vertexShader);

				throw std::runtime_error(infoLog.data());
			}
		}

		Shader::~Shader()
		{
		}

		void Shader::Bind() const
		{
			glUseProgram(m_ProgramID);
		}

		void Shader::Unbind() const
		{
			glUseProgram(0);
		}
	}
}