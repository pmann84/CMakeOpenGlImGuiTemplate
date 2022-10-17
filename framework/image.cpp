#include "image.hpp"
#include "glad/glad.h"

image::image(uint32_t width, uint32_t height, GLenum format) : m_width(width), m_height(height), m_data_format(format)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
    glTextureStorage2D(m_texture_id, 1, m_internal_format, m_width, m_height);
    glBindTextureUnit(0, m_texture_id);
}

void image::resize(uint32_t width, uint32_t height)
{
    if (width != m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
//        glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }
}

void image::set_data(void *data, uint32_t size)
{
//    uint32_t bpp = m_data_format == GL_RGBA ? 4 : 3;
//    HZ_CORE_ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
    glTextureSubImage2D(m_texture_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);
}