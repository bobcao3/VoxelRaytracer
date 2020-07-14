// -------------------------------------------------------------------------------
// VoxelRaytracer - Mesh Formats
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;

	uint32_t materialId;

	glm::vec2 texcoord0;
	glm::vec2 texcoord1;
	glm::vec2 texcoord2;
	glm::vec2 texcoord3;
};

struct Material
{
	glm::vec4 color;
	glm::vec3 emission;
	glm::vec3 transmission;
	float IOR;

	uint32_t texture0;
	uint32_t texture1;
	uint32_t texture2;
	uint32_t texture3;
};

struct Mesh
{
	uint32_t count;
	
	uint32_t vertexOffset;
	uint32_t indexOffset;

	Vertex* vertices;
	uint16_t* indicies;
};