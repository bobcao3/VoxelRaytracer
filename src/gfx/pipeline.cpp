// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Render Pipelines
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "gfx/pipeline.h"
#include "errors.h"

#include <iostream>

void Pipeline::LoadFragmentShader(std::string src)
{
    // Destory old shaders
    if (shaders.fragmentShader)
        glDeleteShader(shaders.fragmentShader);

    // Create & compile new shaders
    const GLchar* srcCString = src.c_str();

    shaders.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaders.fragmentShader, 1, &srcCString, NULL);
    glCompileShader(shaders.fragmentShader);

    // Check for errors
    int  success;
    char infoLog[512]; // Stupid GL, I don't want to pull error message twice
    glGetShaderiv(shaders.fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaders.fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment shaders compilation failed\n" << infoLog << std::endl;
        shaders.fragmentShader = 0;
    }
}

void Pipeline::LoadFragmentShader(std::filesystem::path file)
{
}

void Pipeline::LoadVertexShader(std::string src)
{
    // Destory old shaders
    if (shaders.vertexShader)
        glDeleteShader(shaders.vertexShader);

    // Create & compile new shaders
    const GLchar* srcCString = src.c_str();

    shaders.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaders.vertexShader, 1, &srcCString, NULL);
    glCompileShader(shaders.vertexShader);

    // Check for errors
    int  success;
    char infoLog[512]; // Stupid GL, I don't want to pull error message twice
    glGetShaderiv(shaders.vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaders.vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Vertex shaders compilation failed\n" << infoLog << std::endl;
        shaders.vertexShader = 0;
    }
}

void Pipeline::LoadVertexShader(std::filesystem::path file)
{
}

void Pipeline::LoadComputeShader(std::string src)
{
    // Destory old shaders
    if (shaders.computeShader)
        glDeleteShader(shaders.computeShader);

    // Create & compile new shaders
    const GLchar* srcCString = src.c_str();

    shaders.computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shaders.computeShader, 1, &srcCString, NULL);
    glCompileShader(shaders.computeShader);

    // Check for errors
    int  success;
    char infoLog[512]; // Stupid GL, I don't want to pull error message twice
    glGetShaderiv(shaders.computeShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaders.computeShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Compute shaders compilation failed\n" << infoLog << std::endl;
        shaders.computeShader = 0;
    }
}

void Pipeline::LoadComputeShader(std::filesystem::path file)
{
}

void Pipeline::compile()
{
    // Check whether we had the necessary shaders
    if (type == PipelineType::Raster)
    {
        if (!shaders.fragmentShader || !shaders.vertexShader)
            throw ErrorCode::GFX_SHADERS_NOT_COMPLETE;
    }
    else if (type == PipelineType::Compute)
    {
        if (!shaders.computeShader)
            throw ErrorCode::GFX_SHADERS_NOT_COMPLETE;
    }

    // Destory old shaders program
    if (shaders.program)
    {
        glDeleteProgram(shaders.program);
    }

    // Create & link the program
    shaders.program = glCreateProgram();

    if (type == PipelineType::Raster)
    {
        glAttachShader(shaders.program, shaders.fragmentShader);
        glAttachShader(shaders.program, shaders.vertexShader);
    }
    else if (type == PipelineType::Compute)
    {
        glAttachShader(shaders.program, shaders.computeShader);
    }

    glLinkProgram(shaders.program);

    // Check for errors
    int  success;
    char infoLog[512]; // Stupid GL, I don't want to pull error message twice
    glGetProgramiv(shaders.program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaders.program, 512, NULL, infoLog);
        std::cerr << "ERROR: Shaders linking failed\n" << infoLog << std::endl;
        shaders.program = 0;
    }

    // Remove the shader objects after the program is linked
    if (shaders.fragmentShader)
    {
        glDeleteShader(shaders.fragmentShader);
        shaders.fragmentShader = 0;
    }

    if (shaders.vertexShader)
    {
        glDeleteShader(shaders.vertexShader);
        shaders.vertexShader = 0;
    }

    if (shaders.computeShader)
    {
        glDeleteShader(shaders.computeShader);
        shaders.computeShader = 0;
    }
}

Pipeline::Pipeline(PipelineType t)
    : type(t)
{
}

Pipeline::~Pipeline()
{
    if (shaders.program)
        glDeleteProgram(shaders.program);

    if (shaders.fragmentShader)
        glDeleteShader(shaders.fragmentShader);

    if (shaders.vertexShader)
        glDeleteShader(shaders.vertexShader);

    if (shaders.computeShader)
        glDeleteShader(shaders.computeShader);
}

void VertexArray::AddAttribute(DataType type, uint8_t numComponents, size_t stride, size_t offset, size_t bufferIndex, bool normalized)
{
    Attribute& attr = vertexAttributes.emplace_back();
    attr.type = type;
    attr.numComponents = numComponents;
    attr.stride = stride;
    attr.offset = offset;
    attr.bufferIndex = bufferIndex;
    attr.normalized = normalized;
}

void VertexArray::AddBuffer(Buffer* buf)
{
    buffers.push_back(buf);
}

void VertexArray::SetIndexBuffer(Buffer* buf)
{
    indexBuffer = buf;
}

void VertexArray::BuildArray()
{
    // Destroy old VAO
    if (VAO)
        glDeleteVertexArrays(1, &VAO);

    // Create new VAO
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    uint32_t bufferIndex = 0;
    
    if (indexBuffer)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->buffer);

    for (Buffer* buf : buffers)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buf->buffer);

        uint32_t attrIndex = 0;
        for (Attribute& attr : vertexAttributes) if (attr.bufferIndex == bufferIndex)
        {
            glVertexAttribPointer(attrIndex, GLuint(attr.numComponents), GLenum(attr.type), attr.normalized, GLsizei(attr.stride), (const void*)(attr.offset));
            glEnableVertexAttribArray(attrIndex);

            attrIndex++;
        }

        bufferIndex++;
    }

    glBindVertexArray(0);
}

void VertexArray::UseVertexArray()
{
    glBindVertexArray(VAO);
}

void Pipeline::ScopedExec(std::function<void(Pipeline& p)> func)
{
    glUseProgram(shaders.program);

    func(*this);

    glUseProgram(0);
}

void Pipeline::DrawIndexed(PrimitiveType type, DataType indexFormat, uint32_t count, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceCount, uint32_t instanceOffset)
{
    glDrawElementsInstancedBaseVertexBaseInstance(GLenum(type), count, GLenum(indexFormat), (const void*)(indexOffset), instanceCount, vertexOffset, instanceOffset);
}

void Pipeline::Draw(PrimitiveType type, uint32_t count, uint32_t vertexOffset, uint32_t instanceCount, uint32_t instanceOffset)
{
    glDrawArraysInstancedBaseInstance(GLenum(type), vertexOffset, count, instanceCount, instanceOffset);
}

void Pipeline::Dispatch(uint32_t x, uint32_t y, uint32_t z)
{
    glDispatchCompute(x, y, z);
}

Buffer::Buffer()
{
    glGenBuffers(1, &buffer);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}
