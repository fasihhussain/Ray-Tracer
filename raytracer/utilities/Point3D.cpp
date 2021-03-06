#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <sstream>
Point3D::Point3D() : x(0), y(0), z(0)
{
}

Point3D::Point3D(float c) : x(c), y(c), z(c)
{
}

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

std::string Point3D::to_string() const
{
  std::stringstream ss;
  ss << "Point(" << x << ", " << y << ", " << z << ")";
  return ss.str();
}

Point3D Point3D::operator-() const {
  return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator-(const Point3D& p) const {
  return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D& v) const {
  return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const {
  return Point3D(x - v.x, y - v.y, z - v.z);
}

Point3D Point3D::operator*(const float s) const {
  return Point3D(x * s, y * s, z * s);
}

float Point3D::d_squared(const Point3D &p) const {
  return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}

float Point3D::distance(const Point3D &p) const {
  return std::sqrt(d_squared(p));
}

Point3D operator*(const float a, const Point3D &pt) {
  return pt * a;
}

Point3D min(const Point3D& a, const Point3D& b) {
  return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b) {
  return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}


Point3D Point3D::interpolate(const Point3D &A, const Point3D &B, const Point3D &C, const Point3D &X, const Point3D &Y) {
  float r_x = (C.x-A.x)/(B.x-A.x);
  float r_y = (C.y-A.y)/(B.y-A.y);
  float r_z = (C.z-A.z)/(B.z-A.z);
  return Point3D(r_x*X.x + (1-r_x)*Y.x, r_y*X.y + (1-r_y)*Y.y, r_z*X.z + (1-r_z)*Y.z);
  
}