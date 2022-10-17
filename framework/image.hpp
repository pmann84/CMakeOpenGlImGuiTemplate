#pragma once

#include "glad/glad.h"

#include <cstdint>
#include <vector>

class image
{
public:
    image(uint32_t width, uint32_t height, GLenum format);
    void resize(uint32_t width, uint32_t height);

    uint32_t width() const { return m_width; }
    uint32_t height() const { return m_height; }
    uint32_t id() const { return m_texture_id; }

    void set_data(void* data, uint32_t size);

private:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint32_t m_texture_id;
    GLenum m_internal_format = GL_RGBA8;
    GLenum m_data_format = GL_RGBA;
};
