#include <iostream>

#include "world/World.hpp"
#include "tracers/ShadowTracer.hpp"
#include "tracers/Recursive.hpp"
#include "tracers/AntiAliasing.hpp"
#include "tracers/Tracer.hpp"
#include "tracers/BasicTracer.hpp"

int main(int argc, char **argv)
{
    World world;
    world.build();

    world.add_acceleration_structure();

    
    world.render("scene.ppm");

    return 0;
}
