#include "hkpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hickory
{

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

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		//filtering
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		//free from cpu cache
		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot /*= 0*/) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}