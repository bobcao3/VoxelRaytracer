// -------------------------------------------------------------------------------
// VoxelRaytracer
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_win32.h>

#include <iostream>
#include <string>

#include "errors.h"
#include "gfx/gfx.h"
#include "gfx/pipeline.h"

#include <glm/glm.hpp>

class VoxelTracer
{
private:
    struct Context
    {
        GLFWwindow* window = nullptr;

        int width;
        int height;
    } m_context;

    void RenderScene();
    void RenderUI();
    void Update();

    enum GPUTime {
        GPU3D,
        GPU2D,
        Count
    };

    GPUTimer* timers[GPUTime::Count];
    double frameTimes[GPUTime::Count];

    double framesPerSecond = 0.0;

    // Test content
    struct ShaderConstants
    {
        glm::vec4 color;
    };

    Pipeline pipeline;
    VertexArray vertexArray;
    Buffer* vertexBuffer = nullptr;
    Buffer* indexArray = nullptr;
    Buffer* image = nullptr;
    Buffer* constants = nullptr;
    Texture* texture = nullptr;
    Samplers* sampler = nullptr;

public:
    VoxelTracer();
    ~VoxelTracer();

    void run();
};