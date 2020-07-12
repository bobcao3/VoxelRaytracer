// -------------------------------------------------------------------------------
// VoxelRaytracer
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include <glm/glm.hpp>

#define ERROR_MSGS_IMPL
#include "application.h"

using namespace glm;

void error_callback(int error, const char* description)
{
    std::cerr << "[GLFW] Error: " << description << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ErrorCode& e)
{
    os << "Error code = " << int(e) << ", " << ErrorCodeDesc[int(e)];
    return os;
}

std::string vertexShader = R"V0G0N(

#version 450 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0);
}

)V0G0N";

std::string fragmentShader = R"V0G0N(

#version 450 core

out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 0.4, 0.1, 1.0);
}

)V0G0N";

vec3 vertices[] = {
    vec3(-0.5, -0.5, 0.0),
    vec3( 0.5, -0.5, 0.0),
    vec3( 0.5,  0.5, 0.0),
    vec3(-0.5,  0.5, 0.0)
};

uint16_t indices[] = {
    0, 1, 2,
    3, 0, 2
};

VoxelTracer::VoxelTracer()
    : pipeline(PipelineType::Raster)
{
    // Initialize GLFW & OpenGL Context
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

        if (!glfwInit())
            throw ErrorCode::GLFW_INIT_FAILED;

        glfwSetErrorCallback(error_callback);

        m_context.window = glfwCreateWindow(1280, 720, "VoxelTracer", NULL, NULL);

        glfwMakeContextCurrent(m_context.window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw ErrorCode::GLAD_INIT_FAILED;
    }

    // Initialize imGui
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui_ImplGlfw_InitForOpenGL(m_context.window, false);
        ImGui_ImplOpenGL3_Init("#version 450");

        ImGui::StyleColorsLight();
    }

    // Test content
    pipeline.LoadFragmentShader(fragmentShader);
    pipeline.LoadVertexShader(vertexShader);
    pipeline.compile();

    vertexBuffer = new Buffer();
    vertexBuffer->UploadData<vec3>(vertices, sizeof(vertices));

    indexArray = new Buffer();
    indexArray->UploadData<uint16_t>(indices, sizeof(indices));

    vertexArray.AddBuffer(vertexBuffer);
    vertexArray.SetIndexBuffer(indexArray);
    vertexArray.AddAttribute(DataType::Float, 3, sizeof(vec3), 0, 0);
    vertexArray.BuildArray();
}

VoxelTracer::~VoxelTracer()
{
    // Test content
    delete vertexBuffer;
    // End test content

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_context.window);
    glfwTerminate();
}

void VoxelTracer::RenderScene()
{
    // Test content
    pipeline.ScopedExec([&](Pipeline& p)
        {
            vertexArray.UseVertexArray();
            p.DrawIndexed(PrimitiveType::Triangles, DataType::Uint16, 6, 0, 0, 1, 0);
        });
}

void VoxelTracer::RenderUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render GUI & Controls
    ImGui::Begin("Debug");
    ImGui::Text("VoxelTracer");
    ImGui::End();

    ImGui::Render();
}

void VoxelTracer::Update()
{
    
}

void VoxelTracer::run()
{
    while (!glfwWindowShouldClose(m_context.window))
    {
        // Main Render Loop
        glfwPollEvents();

        glfwGetFramebufferSize(m_context.window, &m_context.width, &m_context.height);
        glViewport(0, 0, m_context.width, m_context.height);

        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        Update();

        RenderScene();

        RenderUI();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_context.window);
    }

}