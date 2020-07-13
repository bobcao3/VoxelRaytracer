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