#include "Triangle.hpp"

Triangle::Triangle()
{
    v0 = Point3D();
    v1 = Point3D();
    v2 = Point3D();
}

Triangle::Triangle(const Point3D &u0, const Point3D &u1, const Point3D &u2)
{
    v0 = u0;
    v1 = u1;
    v2 = u2;
}


Triangle::Triangle(const Triangle &object)
{
    v0 = object.v0;
    v1 = object.v1;
    v2 = object.v2;
}


Triangle &Triangle::operator=(const Triangle &rhs)
{
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    return *this;
}


std::string Triangle::to_string() const
{
    return "v0" + v0.to_string() + 
          ", v1" + v1.to_string() + 
          ", v2" + v2.to_string();
}

bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
    Vector3D u1 = v1 - v0;
    Vector3D u2 = v2 - v0;
    Vector3D n = u1 ^ u2;
    n.normalize();
    
    float r_dot_n = ray.d * n;
    if (r_dot_n == 0)
        return false;
    else if(r_dot_n > 0)
    {
        return false;
        // backside will be invisible
        // try anticlockwise triangle
        n = -n;
        r_dot_n = -r_dot_n;
    }

    t = ((v0 - ray.o) * n)/r_dot_n;
    if (t < 0)
        return false;

    Point3D hit_point = ray.o + ray.d * t;

    float beta = ((hit_point.x - v2.x)*(v0.y - v2.y) - (hit_point.y - v2.y)
    *(v0.x - v2.x)) / ((v1.x - v2.x)*(v0.y - v2.y) - (v1.y - v2.y)
    *(v0.x - v2.x));
    float alpha = ((hit_point.x - v2.x) - (beta) * (v1.x - v2.x)) / (v0.x - v2.x);
    float gamma = 1 - alpha - beta;

    if (0 > alpha || 1 < alpha || 0 > beta || 1 < beta ||  0 > gamma || 1 < gamma)
        return false;
    
    s.t = t;
    s.ray = ray;
    s.hit = true;
    s.hit_point = hit_point;
    s.normal = n;
    s.normal.normalize();
    s.material_ptr = this->get_material();
    
    return true;
}

BBox Triangle::getBBox() const
{
    return BBox(
        min(min(v0,v1),v2),
        max(max(v0,v1),v2)
    );
}

float Triangle::get_area() const
{
    // by area of parallelogram logic
    Vector3D a = (v1 - v0);
    Vector3D b = (v2 - v0);

    return (a ^ b).length() / 2;
}

#include "math.h" // for RAND, and rand

// https://math.stackexchange.com/questions/18686/uniform-random-point-in-triangle-in-3d
Point3D Triangle::pick_random_point() const
{
    double r1 = sqrt((float) rand() / (RAND_MAX));
    double r2 = ((float) rand() / (RAND_MAX));

    return v0*(1-r1) + v1*r1*(1-r2) + v2*r2*r1;
}