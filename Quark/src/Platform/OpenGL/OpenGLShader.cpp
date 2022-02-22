#include "qkpch.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>

QK_PHOTON_BEGIN

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


	uint32_t ShaderDataTypeToOpenGLNativeType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
		case ShaderDataType::Bool2:
		case ShaderDataType::Bool3:
		case ShaderDataType::Bool4:
			return GL_BOOL;

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;

		case ShaderDataType::Uint:
		case ShaderDataType::Uint2:
		case ShaderDataType::Uint3:
		case ShaderDataType::Uint4:
			return GL_UNSIGNED_INT;

		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return GL_FLOAT;

		case ShaderDataType::Double:
		case ShaderDataType::Double2:
		case ShaderDataType::Double3:
		case ShaderDataType::Double4:
			return GL_DOUBLE;

		case ShaderDataType::Mat2:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		}
	}

QK_PHOTON_END
