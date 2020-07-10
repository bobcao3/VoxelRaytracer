// -------------------------------------------------------------------------------
// VoxelRaytracer
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "application.h"

std::string ErrorCodeDesc[] = {
    "None",
    "GLFW failed to initiate",
    "GLAD failed to initiate"
};

void error_callback(int error, const char* description)
{
    std::cerr << "[GLFW] Error: " << description << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ErrorCode& e)
{
    os << "Error code = " << int(e) << ", " << ErrorCodeDesc[int(e)];
    return os;
}

VoxelTracer::VoxelTracer()
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
}

VoxelTracer::~VoxelTracer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_context.window);
    glfwTerminate();
}

void VoxelTracer::RenderScene()
{

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