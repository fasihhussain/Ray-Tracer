#include "Beam.hpp"

Beam::Beam()
{
}

Beam::Beam(float t_, RGBColor color_, Point3D hit_point_, Vector3D direction_)
{
    t = t_;
    color = color_;
    hit_point = hit_point_;
    direction = direction_;
}

Beam::~Beam()
{
}