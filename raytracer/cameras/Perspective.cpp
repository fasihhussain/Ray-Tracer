#include "Perspective.hpp"
#include "../utilities/Vector3D.hpp"
Perspective::Perspective() : Camera(){
  pos = Point3D();
}

Perspective::Perspective(float c): Camera() {
  pos = Point3D(c);
}

Perspective::Perspective(float x, float y, float z): Camera() {
  pos = Point3D(x,y,z);
}

Perspective::Perspective(const Point3D& pt) : Camera(){
  pos = pt;
}

Perspective::Perspective(const Perspective& p) : Camera(p) {
  pos = p.pos;
}

Vector3D Perspective::get_direction(const Point3D& p) const {
  // Find the direction vector from the camera position to the point p
  Vector3D dir = (p-pos);
  // Normalize and return the result
  dir.normalize();
  return dir;
}