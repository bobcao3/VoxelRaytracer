// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Common
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <glad/glad.h>

enum class PrimitiveType
{
    Triangles = GL_TRIANGLES,
    Lines = GL_LINES,
    Points = GL_POINTS
};

enum class DataType
{
    Uint32 = GL_UNSIGNED_INT,
    Int32 = GL_INT,
    Uint16 = GL_UNSIGNED_SHORT,
    Int16 = GL_SHORT,
    Uint8 = GL_UNSIGNED_BYTE,
    Int8 = GL_BYTE,
    Float = GL_FLOAT,
    Float16 = GL_HALF_FLOAT,
    Fixed16 = GL_FIXED
};

enum class PipelineType
{
    Raster,
    Compute
};

enum class BufferAccess
{
    ReadOnly = GL_READ_ONLY,
    WriteOnly = GL_WRITE_ONLY,
    ReadWrite = GL_READ_WRITE
};

enum class TextureType
{
    Tex1D = GL_TEXTURE_1D,
    Tex2D = GL_TEXTURE_2D,
    Tex3D = GL_TEXTURE_3D
};

enum class BufferFormat
{
    R8I = GL_R8I,
    R8UI = GL_R8UI,
    R8Unorm = GL_R8,
    R8Snorm = GL_R8_SNORM,

    R16F = GL_R16F,
    R16I = GL_R16I,
    R16UI = GL_R16UI,
    R16Unorm = GL_R16,
    R16Snorm = GL_R16_SNORM,

    R32F = GL_R32F,
    R32I = GL_R32I,
    R32UI = GL_R32UI,

    RG8I = GL_RG8I,
    RG8UI = GL_RG8UI,
    RG8Unorm = GL_RG8,
    RG8Snorm = GL_RG8_SNORM,

    RG16F = GL_RG16F,
    RG16I = GL_RG16I,
    RG16UI = GL_RG16UI,
    RG16Unorm = GL_RG16,
    RG16Snorm = GL_RG16_SNORM,

    RG32F = GL_RG32F,
    RG32I = GL_RG32I,
    RG32UI = GL_RG32UI,

    R3G3B2 = GL_R3_G3_B2,

    RGB8I = GL_RGB8I,
    RGB8UI = GL_RGB8UI,
    RGB8Unorm = GL_RGB8,
    RGB8Snorm = GL_RGB8_SNORM,

    RGB9E5 = GL_RGB9_E5,

    R11G11B10 = GL_R11F_G11F_B10F,

    RGB16F = GL_RGB16F,
    RGB16I = GL_RGB16I,
    RGB16UI = GL_RGB16UI,
    RGB16Unorm = GL_RGB16,
    RGB16Snorm = GL_RGB16_SNORM,

    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB32UI = GL_RGB32UI,

    RGB10A2 = GL_RGB10_A2,

    RGBA16F = GL_RGBA16F,
    RGBA16I = GL_RGBA16I,
    RGBA16UI = GL_RGBA16UI,
    RGBA16Unorm = GL_RGBA16,
    RGBA16Snorm = GL_RGBA16_SNORM,

    RGBA32F = GL_RGBA32F,
    RGBA32I = GL_RGBA32I,
    RGBA32UI = GL_RGBA32UI,

    Unkown = GL_ZERO
};