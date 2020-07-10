// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System - Render Pipelines
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <functional>
#include <string>

class VertexArray;

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

class Pipeline
{
private:
	enum class PipelineType
	{
		Raster,
		Compute
	};

	PipelineType type = PipelineType::Raster;

public:
	// Shader Creation
	void LoadFragmentShader(std::string src);
	void LoadFragmentShader(std::filesystem::path file);

	void LoadVertexShader(std::string src);
	void LoadVertexShader(std::filesystem::path file);

	void LoadComputeShader(std::string src); // Doing so will set the pipeline type to compute
	void LoadComputeShader(std::filesystem::path file);

	void compile();

	~Pipeline();

	// Input Attributes - only useful for Raster pipeline
	void AddAttribute(DataType type, uint8_t numComponents, size_t stride, size_t offset, bool normalized = false);

	// Pipeline execution
	void ScopedExec(std::function<void(Shaders& s)> func);

	// Raster Pipeline
	void SetVertexArray(VertexArray& vao);
	void DrawIndexed(PrimitiveType type, DataType indexFormat, uint32_t count, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);
	void Draw(PrimitiveType type, uint32_t count, uint32_t vertexOffset, uint32_t instanceCount = 1, uint32_t instanceOffset = 0);

	// Compute Pipeline
	void Dispatch(uint32_t x, uint32_t y, uint32_t z);
};