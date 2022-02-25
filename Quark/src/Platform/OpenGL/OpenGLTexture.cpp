#include "qkpch.hpp"
#include "OpenGLTexture.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

QK_PHOTON_BEGIN
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
		m_Path(path), m_Width(0), m_Height(0), m_Texture(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	
		QK_CORE_ASSERT(data, "Failed to load image {0}", path);

		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
		glTextureStorage2D(m_Texture, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glTextureSubImage2D(m_Texture, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, (void*)data);

		stbi_image_free((void*)data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_Texture);
	}

QK_PHOTON_END

