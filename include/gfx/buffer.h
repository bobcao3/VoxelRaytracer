// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Buffers (GPU Memory)
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include "gfx.h"

#include <cstdint>

class Buffer
{
public:
    uint32_t buffer = 0;
    size_t size = 0;

    Buffer();
    Buffer(size_t size);
    ~Buffer();

    template <typename T> void UploadData(T* data, size_t numElements);
    template <typename T> void UploadDataRange(T* data, size_t index, size_t numElements);

    template <typename T> T* Map(BufferAccess access);
    template <typename T> T* MapRange(BufferAccess access, size_t index, size_t length);
    
    void Unmap();
};

class Samplers
{
public:
    enum class FilterMode
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestTextureNearestMipMap = GL_NEAREST_MIPMAP_NEAREST,
        LinearTextureNearestMipMap = GL_LINEAR_MIPMAP_NEAREST,
        NearestTextureLinearMipMap = GL_NEAREST_MIPMAP_LINEAR,
        LinearTextureLinearMipMap = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class WrapMode
    {
        Clamp = GL_CLAMP_TO_EDGE,
        Mirror = GL_MIRRORED_REPEAT,
        Repeat = GL_REPEAT,
        MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
    };

    uint32_t sampler = 0;

    FilterMode minFilter = FilterMode::Linear;
    FilterMode magFilter = FilterMode::Linear;

    WrapMode wrapS = WrapMode::Repeat;
    WrapMode wrapT = WrapMode::Repeat;
    WrapMode wrapR = WrapMode::Repeat;

    Samplers();

    void UpdateParams();
};

class Texture
{
public:
    enum class ImageFormat
    {
        R = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA,
        BGR = GL_BGR,
        BGRA = GL_BGRA
    };

    uint32_t texture = 0;

    size_t width = 0;
    size_t height = 0;
    size_t depth = 0;
    size_t levels = 0;

    BufferFormat format = BufferFormat::Unkown;
    TextureType type;

    Texture(BufferFormat format, size_t width, size_t levels);
    Texture(BufferFormat format, size_t width, size_t height, size_t levels);
    Texture(BufferFormat format, size_t width, size_t height, size_t depth, size_t levels);
    ~Texture();

    void UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t width, const void* data);
    void UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t yOffset, size_t width, size_t height, const void* data);
    void UploadImage(ImageFormat format, DataType type, size_t level, size_t xOffset, size_t yOffset, size_t zOffset, size_t width, size_t height, size_t depth, const void* data);
};

template<typename T>
inline void Buffer::UploadData(T* data, size_t numElements)
{
    glNamedBufferData(buffer, sizeof(T) * numElements, reinterpret_cast<uint8_t*>(data), GL_STATIC_DRAW);
}

template<typename T>
inline void Buffer::UploadDataRange(T* data, size_t index, size_t numElements)
{
    glNamedBufferSubData(buffer, sizeof(T) * index, sizeof(T) * numElements, reinterpret_cast<uint8_t*>(data), GL_STATIC_DRAW);
}

template<typename T>
inline T* Buffer::Map(BufferAccess access)
{
    return reinterpret_cast<T*>(glMapNamedBuffer(buffer, GLenum(access)));
}

template<typename T>
inline T* Buffer::MapRange(BufferAccess access, size_t index, size_t length)
{
    return reinterpret_cast<T*>(glMapNamedBufferRange(buffer, sizeof(T) * index, sizeof(T) * length, GLenum(access)));
}
