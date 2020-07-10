// -------------------------------------------------------------------------------
// VoxelRaytracer - Ray Tracing Engine
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#pragma once

#include <functional>
#include <limits>

#include <glm/glm.hpp>

// Use 32-bit precision
typedef float Float;
typedef int32_t Int;
typedef uint32_t UInt;
typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat2 Mat2;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

const Float MaxFloat = std::numeric_limits<Float>::max();
const Float EPS = 0.00001f;

class Ray
{
public:
	Vec3 Direction;
	Float MinT;
	Vec3 InvDirection; // rcp of Direction
	Float MaxT;

	Ray(Vec3 Direction, Float MinT = EPS, Float MaxT = MaxFloat);
};

class Scene
{
public:
	class Context;

	virtual Context* LaunchRay() = 0;
	virtual bool NextIntersection(Context* ctx, Ray& r) = 0;
};

class RayTracing
{
public:
	enum class AnyHitBehavior
	{
		COMMIT_AND_CONTINUE,
		IGNORE_AND_CONTINUE,
		COMMIT_AND_RETURN,
		CALL_HANDLER
	};

	enum class ClosestHitBehavior
	{
		RETURN,
		CALL_HANDLER
	};

	std::function<ClosestHitBehavior(const RayTracing&, const Ray&, void*)> cloestHitHandler = nullptr;
	std::function<AnyHitBehavior(const RayTracing&, const Ray&, void*)> anyHitHandler = nullptr;

	void TraceRay(
		Scene* sc,
		Ray& r,
		AnyHitBehavior anyHitFlag = AnyHitBehavior::COMMIT_AND_CONTINUE,
		ClosestHitBehavior closestHitFlag = ClosestHitBehavior::RETURN,
		void* payload = nullptr
		);
};