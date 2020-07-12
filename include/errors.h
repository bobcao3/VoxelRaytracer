// -------------------------------------------------------------------------------
// VoxelRaytracer - Errors
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

enum class ErrorCode
{
    NO_ERROR,
    GLFW_INIT_FAILED,
    GLAD_INIT_FAILED,
    GFX_SHADERS_NOT_COMPLETE
};

#ifdef ERROR_MSGS_IMPL

std::string ErrorCodeDesc[] = {
    "None",
    "GLFW failed to initiate",
    "GLAD failed to initiate"
    "The shaders specified are not complete (missing shader stages)"
};

#endif