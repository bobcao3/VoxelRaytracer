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

#include <iostream>
#include <string>

#include "errors.h"
#include "gfx/pipeline.h"

std::ostream& operator<<(std::ostream& os, const ErrorCode& e);

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

    // Test content
    Pipeline pipeline;
    Buffer* vertexBuffer = nullptr;
    Buffer* indexArray = nullptr;
    VertexArray vertexArray;

public:
    VoxelTracer();
    ~VoxelTracer();

    void run();
};