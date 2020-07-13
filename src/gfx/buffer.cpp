// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Buffers (GPU Memory)
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "gfx/buffer.h"

Buffer::Buffer()
{
    glCreateBuffers(1, &buffer);
}

Buffer::Buffer(size_t size) : Buffer()
{
    glNamedBufferData(buffer, size, nullptr, GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

void Buffer::Unmap()
{
    glUnmapNamedBuffer(buffer);
}

Texture::Texture(BufferFormat format, size_t width, size_t levels)
{
    glCreateTextures(GL_TEXTURE_1D, 1, &texture);
    glTextureStorage1D(texture, levels, GLenum(format), width);

    this->width = width;
    this->levels = levels;

    this->format = format;
    this->type = TextureType::Tex1D;
}

Texture::Texture(BufferFormat format, size_t width, size_t height, size_t levels)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, levels, GLenum(format), width, height);

    this->width = width;
    this->height = height;
    this->levels = levels;

    this->format = format;
    this->type = TextureType::Tex2D;
}

Texture::Texture(BufferFormat format, size_t width, size_t height, size_t depth, size_t levels)
{
    glCreateTextures(GL_TEXTURE_3D, 1, &texture);
    glTextureStorage3D(texture, levels, GLenum(format), width, height, depth);

    this->width = width;
    this->height = height;
    this->depth = depth;
    this->levels = levels;

    this->format = format;
    this->type = TextureType::Tex3D;
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

void Texture::UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t width, const void* data)
{
    glTextureSubImage1D(texture, level, xOffset, width, GLenum(format), GLenum(type), data);
}

void Texture::UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t yOffset, size_t width, size_t height, const void* data)
{
    glTextureSubImage2D(texture, level, xOffset, yOffset, width, height, GLenum(format), GLenum(type), data);
}

void Texture::UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t yOffset, size_t zOffset, size_t width, size_t height, size_t depth, const void* data)
{
    glTextureSubImage3D(texture, level, xOffset, yOffset, zOffset, width, height, depth, GLenum(format), GLenum(type), data);
}


Samplers::Samplers()
{
    glCreateSamplers(1, &sampler);

    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GLenum(minFilter));
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GLenum(magFilter));

    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GLenum(wrapS));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GLenum(wrapT));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, GLenum(wrapR));
}

void Samplers::UpdateParams()
{
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GLenum(minFilter));
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GLenum(magFilter));

    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GLenum(wrapS));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GLenum(wrapT));
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, GLenum(wrapR));
}
