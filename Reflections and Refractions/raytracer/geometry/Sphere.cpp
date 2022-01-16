#include "Sphere.hpp"
#include <iostream>

Sphere::Sphere()
{
    this->c = Point3D(0.0, 0.0, 0.0);
    this->r = 0.0;
}

Sphere::Sphere(const Point3D &center, float radius)
{
    this->c = center;
    this->r = radius;
}

Sphere::Sphere(const Sphere &object)
{
    this->c = object.c;
    this->r = object.r;
}
  
Sphere &Sphere::operator=(const Sphere &rhs)
{
    c = rhs.c;
    r = rhs.r;
    return *this;
}

std::string Sphere::to_string() const
{
    return "c" + this->c.to_string() +
            ", r=" + std::to_string(r);
}

bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
    Vector3D d = this->c - ray.o;
    float r_dot_d = ray.d * d;
    float ray_2 = ray.d.len_squared();
    float D = ray_2*(-d.len_squared() + r*r) + r_dot_d*r_dot_d;

    if (D < 0.0)
        return false;

    if (ray_2 < kEpsilon)
        return false;

    float t1 = (r_dot_d - sqrt(D)) / ray_2;
    float t2 = (r_dot_d + sqrt(D)) / ray_2;

    if (t1 >= 0) 
        t = t1;
    else if (t2 >= 0) 
        t = t2;
    else 
        return false;

    
    s.t = t;
    s.hit = true;
    s.ray = ray;
    s.hit_point = ray.o + ray.d * t;
    s.normal = s.hit_point - c;
    s.normal.normalize();
    s.material_ptr = this->get_material();
    
    return true;
}

BBox Sphere::getBBox() const
{
    return BBox(
      c - Vector3D(r,r,r),
      c + Vector3D(r,r,r)
    );
}

float Sphere::get_area() const
{
    return 4*PI*r*r;
}

#include "math.h" // for RAND, and rand
double sampleNormal() {
    double u = ((float) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((float) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}

// Pick random point uniformly
Point3D Sphere::pick_random_point() const
{
    double x = sampleNormal(),y = sampleNormal(),z = sampleNormal();
    Vector3D v(x, y, z);
    v.normalize();
    Point3D sample = this->c + r*v;
    // std::cout << sample.to_string() << std::endl;
    return this->c + r*v;
}