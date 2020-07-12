// -------------------------------------------------------------------------------
// VoxelRaytracer - Ray Tracing Engine
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "raytracing.h"
#include "..\include\raytracing.h"

Ray::Ray(Vec3 Direction, Float MinT, Float MaxT)
    : Direction(Direction)
    , InvDirection(Vec3(1.0) / Direction)
    , MinT(MinT)
    , MaxT(MaxT)
{
}

void RayTracing::TraceRay(Scene* sc, Ray& r, AnyHitBehavior anyHitFlag, ClosestHitBehavior closestHitFlag, void* payload)
{
    Scene::Context* ctx = sc->LaunchRay();
    Ray tempRay = r;

    AnyHitBehavior anyhit = AnyHitBehavior::COMMIT_AND_CONTINUE;
    bool hasHit = false;

    // An actually very powerful state machine
    while (sc->NextIntersection(ctx, tempRay))
    {
        if (anyHitFlag == AnyHitBehavior::CALL_HANDLER && anyHitHandler)
            anyhit = anyHitHandler(*this, tempRay, payload);
        else
            anyhit = anyHitFlag;

        if (anyhit == AnyHitBehavior::COMMIT_AND_CONTINUE || anyhit == AnyHitBehavior::COMMIT_AND_RETURN)
        {
            r.MaxT = tempRay.MaxT;
            r.MinT = tempRay.MinT;
            hasHit = true;
        }
        
        if (anyhit == AnyHitBehavior::COMMIT_AND_RETURN) break;
    }

    if (hasHit && cloestHitHandler)
        cloestHitHandler(*this, r, payload);
}
