// -------------------------------------------------------------------------------
// VoxelRaytracer
// -------------------------------------------------------------------------------
//  Cheng (Bob) Cao 2020

#include "application.h"

int main(int argc, char** argv)
{
    try
    {
        VoxelTracer app;

        app.run();
    }
    catch (ErrorCode e)
    {
        std::cerr << "[Error] " << e << std::endl;
        return -1;
    }

    return 0;
}