#-------------------------------------------------------------------------------
# Project: VoxelRaytracer
#-------------------------------------------------------------------------------
# Cheng (Bob) Cao 2020
# 
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8)
project(VoxelRaytracer
    VERSION 0.0
)

#-------------------------------------------------------------------------------
# Application Source & Headers
#-------------------------------------------------------------------------------

set(APPLICATION_SOURCE
    # Main Application
    src/main.cpp
    src/voxel_tracer.cpp

    # GLAD
    external/glad/src/glad.c

    # imGui
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/examples/imgui_impl_glfw.cpp
    external/imgui/examples/imgui_impl_opengl3.cpp
)

#-------------------------------------------------------------------------------
# Binaries
#-------------------------------------------------------------------------------

add_executable(tracer ${APPLICATION_SOURCE})

#-------------------------------------------------------------------------------
# Find Dependencies
#-------------------------------------------------------------------------------

# Compiled dependencies

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(tracer PUBLIC OpenGL::GL glfw ${CMAKE_DL_LIBS})

# Headers

target_include_directories(tracer PUBLIC include)
target_include_directories(tracer PUBLIC external/glfw/include)
target_include_directories(tracer PUBLIC external/glad/include)
target_include_directories(tracer PUBLIC external/glm/include)
target_include_directories(tracer PUBLIC external/imgui)

#-------------------------------------------------------------------------------
# Set Compiler Options
#-------------------------------------------------------------------------------

set_property(TARGET tracer PROPERTY CXX_STANDARD 17)
