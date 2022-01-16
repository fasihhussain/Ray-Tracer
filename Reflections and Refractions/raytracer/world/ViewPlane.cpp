#include "ViewPlane.hpp"

ViewPlane::ViewPlane()
{
    hres = 640;
    vres = 480;
    top_left = Point3D(-320, 240, 0);
    bottom_right = Point3D(320, -240, 0);
    normal = Vector3D(0, 0, -1);
}


int ViewPlane::get_hres() const
{
    return hres;
}
  
void ViewPlane::set_hres(int h)
{
    hres = h;
}

int ViewPlane::get_vres() const
{
    return vres;
}

void ViewPlane::set_vres(int v)
{
    vres = v;
}
