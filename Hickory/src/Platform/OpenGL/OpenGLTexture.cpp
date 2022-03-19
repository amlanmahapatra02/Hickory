#include "hkpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hickory
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		//filtering
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;

		//bcz Opengl expect texture in bottom to top manner (inverted)
		stbi_set_flip_vertically_on_load(1);

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HK_CORE_ASSERT(data, "Failed to load Image !");

		m_Width = width;
		m_Height = height;

		GLenum openglinternalFormat = 0, opengldataformat = 0;

		if (channels == 4)
		{
			openglinternalFormat = GL_RGBA8;
			opengldataformat = GL_RGBA;
		}

		else if (channels == 3)
		{
			openglinternalFormat = GL_RGB8;
			opengldataformat = GL_RGB;
		}

		m_InternalFormat = openglinternalFormat;
		m_DataFormat = opengldataformat;

		HK_CORE_ASSERT(openglinternalFormat & opengldataformat, "Format not Supported");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		glTextureStorage2D(m_RendererID, 1, openglinternalFormat, m_Width, m_Height);

		//filtering
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, opengldataformat, GL_UNSIGNED_BYTE, data);

		//free from cpu cache
		stbi_image_free(data);

	}

	

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		HK_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be Entire Texture");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot /*= 0*/) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}