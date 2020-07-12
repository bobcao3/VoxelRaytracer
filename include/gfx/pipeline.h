// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Render Pipelines
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <functional>
#include <string>

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

class Buffer
{
public:
    uint32_t buffer = 0;

    Buffer();
    ~Buffer();

    template <typename T> void UploadData(T* data, size_t numElements);
};

class VertexArray
{
private:
    uint32_t VAO = 0;

public:
    struct Attribute
    {
        DataType type;
        uint8_t numComponents;
        size_t stride;
        size_t offset;
        size_t bufferIndex;
        bool normalized;
    };

    std::vector<Attribute> vertexAttributes;
    std::vector<Buffer*> buffers;

    Buffer* indexBuffer = nullptr;

    void AddAttribute(DataType type, uint8_t numComponents, size_t stride, size_t offset, size_t bufferIndex, bool normalized = false);
    void AddBuffer(Buffer* buf);
    void SetIndexBuffer(Buffer* buf);
    void BuildArray();
    void UseVertexArray();
};

enum class PipelineType
{
    Raster,
    Compute
};

class Pipeline
{
private:
    PipelineType type = PipelineType::Raster;

    struct GLShaders
    {
        uint32_t fragmentShader = 0;
        uint32_t vertexShader = 0;
        uint32_t computeShader = 0;

        uint32_t program = 0;
    } shaders;

public:
    // Shader Creation
    void LoadFragmentShader(std::string src);
    void LoadFragmentShader(std::filesystem::path file);

    void LoadVertexShader(std::string src);
    void LoadVertexShader(std::filesystem::path file);

    void LoadComputeShader(std::string src); // Doing so will set the pipeline type to compute
    void LoadComputeShader(std::filesystem::path file);

    void compile();

    Pipeline(PipelineType t);
    ~Pipeline();

    // Pipeline execution
    void ScopedExec(std::function<void(Pipeline& p)> func);

    // Raster Pipeline
    void DrawIndexed(PrimitiveType type, DataType indexFormat, uint32_t count, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);
    void Draw(PrimitiveType type, uint32_t count, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);

    // Compute Pipeline
    void Dispatch(uint32_t x, uint32_t y, uint32_t z);
};

template<typename T>
inline void Buffer::UploadData(T* data, size_t numElements)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * numElements, reinterpret_cast<uint8_t*>(data), GL_STATIC_DRAW);
}
