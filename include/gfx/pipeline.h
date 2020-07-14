// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Render Pipelines
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <filesystem>
#include <functional>
#include <string>

#include "gfx.h"
#include "buffer.h"

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

    struct BufferBindings
    {
        Buffer* buffer;
        size_t offset;
        size_t stride;
    };

    std::vector<Attribute> vertexAttributes;
    std::vector<BufferBindings> buffers;

    Buffer* indexBuffer = nullptr;

    void AddAttribute(DataType type, uint8_t numComponents, size_t stride, size_t offset, size_t bufferIndex, bool normalized = false);
    void AddBuffer(Buffer* buf, size_t offset, size_t stride);
    void SetIndexBuffer(Buffer* buf);
    void BuildArray();
    void UseVertexArray();
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

#ifdef DEBUG
    bool inScope = false;
#endif

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

    // Resource bindings & constant buffers
    void BindTexture(size_t bindPoint, Texture* texture);
    void BindSamplers(size_t bindPoint, Samplers* sampler);
    void BindConstants(size_t bindPoint, size_t offset, size_t size, Buffer* buffer);

    // Raster Pipeline
    void DrawIndexed(PrimitiveType type, DataType indexFormat, uint32_t count, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);
    void Draw(PrimitiveType type, uint32_t count, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);

    // Compute Pipeline
    void Dispatch(uint32_t x, uint32_t y, uint32_t z);
};