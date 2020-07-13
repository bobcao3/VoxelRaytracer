// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Buffers (GPU Memory)
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "gfx/buffer.h"

Buffer::Buffer()
{
    glCreateBuffers(1, &buffer);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}
