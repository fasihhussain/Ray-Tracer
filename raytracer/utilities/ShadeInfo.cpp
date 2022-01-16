#include "ShadeInfo.hpp"
#include "../world/World.hpp"

ShadeInfo::ShadeInfo(const World &wr) {
  hit = false;
  material_ptr = nullptr;
  hit_point = Point3D(0, 0, 0);
  normal = Vector3D(0, 0, 1);
  ray = Ray(Point3D(0, 0, 0), Vector3D(0, 0, 0));
  depth = 0;
  t = 0;
  w = &wr;
}
