#include "Plane.hpp"

Plane::Plane()
{
    this->a = Point3D(0, 0, 0);
    this->n = Vector3D(0, 1, 0);
}

Plane::Plane(const Point3D &pt, const Vector3D &n)
{
    this->a = pt;
    this->n = n;
    this->n.normalize();
}

Plane::Plane(const Plane &object)
{
    this->a = object.a;
    this->n = object.n;
}

Plane &Plane::operator=(const Plane &rhs)
{
    a = rhs.a;
    n = rhs.n;
    return *this;
}

std::string Plane::to_string() const
{
    return "a" + this->a.to_string() +
            ", n" + this->n.to_string();
}

bool Plane::hit(const Ray &ray, float &t, ShadeInfo &sinfo) const
{
    float r_dot_n = ray.d * this->n;
    if (r_dot_n == 0)
        return false;

    t = ((this->a - ray.o) * this->n) / r_dot_n;
    if (t < 0) 
        return false;

    
    sinfo.t = t;
    sinfo.hit = true;
    sinfo.ray = ray;
    sinfo.normal = this->n;
    sinfo.normal.normalize();
    sinfo.hit_point = ray.o + ray.d * t;
    sinfo.material_ptr = this->get_material();
    
    return true;
}

BBox Plane::getBBox() const
{    
    return BBox(
        Point3D(-kHugeValue,-kHugeValue,-kHugeValue), 
        Point3D(kHugeValue, kHugeValue, kHugeValue)
    );
}


float Plane::get_area() const
{
    return kHugeValue;
}


Point3D Plane::pick_random_point() const
{
    return this->a;
}