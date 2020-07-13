// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Buffers (GPU Memory)
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

class Buffer
{
public:
    uint32_t buffer = 0;

    Buffer();
    ~Buffer();

    template <typename T> void UploadData(T* data, size_t numElements);
    template <typename T> void UploadDataRange(T* data, size_t index, size_t numElements);

    template <typename T> T* Map(BufferAccess access);
    template <typename T> T* MapRange(BufferAccess access, size_t index, size_t length);
};

class Texture
{
public:
    uint32_t texture = 0;

    Texture();
    ~Texture();
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
