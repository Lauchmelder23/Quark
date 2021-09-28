#include "qkpch.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
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

			m_Program = glCreateProgram();
			glAttachShader(m_Program, vertexShader);
			glAttachShader(m_Program, fragmentShader);
			glLinkProgram(m_Program);

			GLint isLinked = 0;
			glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(m_Program, maxLength, &maxLength, infoLog.data());

				glDeleteProgram(m_Program);
				glDeleteShader(fragmentShader);
				glDeleteShader(vertexShader);

				throw std::runtime_error(infoLog.data());
			}
		}

		OpenGLShader::~OpenGLShader()
		{
			glDeleteProgram(m_Program);
		}

		void OpenGLShader::Bind() const
		{
			glUseProgram(m_Program);
		}

		void OpenGLShader::Unbind() const
		{
			glUseProgram(0);
		}
	}
}