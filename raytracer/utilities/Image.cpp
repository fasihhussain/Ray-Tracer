#include "Image.hpp"
#include "RGBColor.hpp"
#include "../world/ViewPlane.hpp"
#include <fstream>

Image::Image(int hres, int vres) : hres(hres), vres(vres)
{
  // make rows of pixels
  colors = new RGBColor *[vres];
  for (int i = 0; i < vres; i++)
  {
    // each row of pixel has hres pixels.
    colors[i] = new RGBColor[hres];
  }
}

Image::Image(const ViewPlane &vp) : hres(vp.hres), vres(vp.vres)
{
  // make rows of pixels
  colors = new RGBColor *[vres];
  for (int i = 0; i < vres; i++)
  {
    // each row of pixel has hres pixels.
    colors[i] = new RGBColor[hres];
  }
}
Image::~Image()
{
  for (int i = 0; i < vres; i++)
  {
    if (colors[i])
    {
      delete[] colors[i];
    }
    colors[i] = nullptr;
  }
  delete[] colors;
  colors = nullptr;
}

void Image::set_pixel(int x, int y, const RGBColor &color)
{
  // x : row
  // y : column
  colors[y][x] = color;
}

RGBColor Image::get_pixel(int x, int y)
{
  // x : row
  // y : column
  return colors[y][x];
}

void Image::write_ppm(std::string path) const
{
  std::ofstream out(path);

  out << "P3\n"
      << hres << " " << vres << "\n255\n";

  // For each row
  for (int i = 0; i < vres; i++)
  {
    // Write each pixel in the row
    for (int j = 0; j < hres; j++)
    {
      out << colors[i][j].to_string() << " ";
    }
    out << "\n";
  }
  out.close();
}