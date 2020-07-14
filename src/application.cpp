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

out vec2 texcoord;

void main()
{
    texcoord = position.st;
    gl_Position = vec4(position, 1.0);
}

)V0G0N";

std::string fragmentShader = R"V0G0N(

#version 450 core

layout(binding = 0) uniform sampler2D tex;

layout(std140, binding = 1) uniform ShaderConstants
{
    vec4 color;
};

out vec4 fragColor;

in vec2 texcoord;

void main()
{
    fragColor = vec4(texture(tex, texcoord, 0).rgb, 1.0) * color;
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

    // Initialize timers
    for (int i = 0; i < GPUTime::Count; i++)
    {
        timers[i] = new GPUTimer();
    }

    // Test content
    pipeline.LoadFragmentShader(fragmentShader);
    pipeline.LoadVertexShader(vertexShader);
    pipeline.compile();

    vertexBuffer = new Buffer();
    vertexBuffer->UploadData(vertices, sizeof(vertices));

    indexArray = new Buffer();
    indexArray->UploadData(indices, sizeof(indices));

    sampler = new Samplers();

    vec4 image[50][50];
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            int fun = i ^ j;
            image[i][j] = vec4((fun % 3 == 0) ? 0.0 : 1.0, (fun % 3 == 1) ? 0.0 : 1.0, (fun % 3 == 2) ? 0.0 : 1.0, 1.0);
        }
    }

    texture = new Texture(BufferFormat::RGBA32F, 50, 50, 1);
    texture->UploadImage(Texture::ImageFormat::RGBA, DataType::Float, 0, 0, 0, 50, 50, image);

    sampler = new Samplers();

    vertexArray.AddBuffer(vertexBuffer, 0, sizeof(vec3));
    vertexArray.SetIndexBuffer(indexArray);
    vertexArray.AddAttribute(DataType::Float, 3, sizeof(vec3), 0, 0);
    vertexArray.BuildArray();

    constants = new Buffer(sizeof(ShaderConstants));
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
            ShaderConstants* consts = constants->Map<ShaderConstants>(BufferAccess::WriteOnly);
            consts->color = vec4(1.0, 0.0, 1.0, 1.0);
            constants->Unmap();

            vertexArray.UseVertexArray();
            p.BindTexture(0, texture);
            p.BindSamplers(0, sampler);
            p.BindConstants(1, 0, sizeof(ShaderConstants), constants);
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

    ImGui::Separator();

    ImGui::Text("FPS Avg: %f", framesPerSecond);
    ImGui::Text("3D: %fms", frameTimes[GPU3D]);
    ImGui::Text("2D: %fms", frameTimes[GPU2D]);

    ImGui::End();

    ImGui::Render();
}

void VoxelTracer::Update()
{
    
}

void VoxelTracer::run()
{
    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_context.window))
    {
        double currentTime = glfwGetTime();
        framesPerSecond = framesPerSecond * 0.9 + 1.0 / (currentTime - previousTime) * 0.1;
        previousTime = currentTime;

        // Main Render Loop
        glfwPollEvents();

        glfwGetFramebufferSize(m_context.window, &m_context.width, &m_context.height);
        glViewport(0, 0, m_context.width, m_context.height);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Update();

        timers[GPU3D]->Start();
        RenderScene();
        timers[GPU3D]->End();

        timers[GPU2D]->Start();
        RenderUI();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        timers[GPU2D]->End();

        frameTimes[GPU3D] = timers[GPU3D]->getTimeSpent();
        frameTimes[GPU2D] = timers[GPU2D]->getTimeSpent();

        glfwSwapBuffers(m_context.window);
    }

}