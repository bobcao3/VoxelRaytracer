// -------------------------------------------------------------------------------
// VoxelRaytracer - GFX System
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "gfx/gfx.h"

GPUTimer::GPUTimer()
{
    glGenQueries(2, queryID);
}

void GPUTimer::Start()
{
    glQueryCounter(queryID[0], GL_TIMESTAMP);
}

void GPUTimer::End()
{
    glQueryCounter(queryID[1], GL_TIMESTAMP);
}

double GPUTimer::getTimeSpent()
{
    GLint stopTimerAvailable = 0;
    while (!stopTimerAvailable) {
        glGetQueryObjectiv(queryID[1],
            GL_QUERY_RESULT_AVAILABLE,
            &stopTimerAvailable);
    }

    glGetQueryObjectui64v(queryID[0], GL_QUERY_RESULT, &startTime);
    glGetQueryObjectui64v(queryID[1], GL_QUERY_RESULT, &stopTime);

    return double(stopTime - startTime) / 1000000.0;
}