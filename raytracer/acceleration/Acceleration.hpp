#pragma once
#include <vector>
#include "../geometry/Geometry.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
class Acceleration
{
private:
    /* data */
public:
    Acceleration() = default;
    // Copy Constructor
    Acceleration(const Acceleration &other) = default;
    // Assignment operator
    Acceleration &operator=(const Acceleration &other) = default;
    // Hit objects in the world with a ray.
    virtual ShadeInfo hit_objects(const Ray &ray,ShadeInfo& shade_info) const = 0;
    // Destructor.
    virtual ~Acceleration() = default;
};
