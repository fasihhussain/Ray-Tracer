#pragma once


#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/RGBColor.hpp"


class Beam
{
public:
    float t;
    RGBColor color; 
    Point3D hit_point;
    Vector3D direction;

    Beam();
    Beam(float, RGBColor, Point3D, Vector3D);
    ~Beam();
};