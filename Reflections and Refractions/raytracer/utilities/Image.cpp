#include "Image.hpp"

#include <iostream>
#include <fstream>

// Constructors.
Image::Image(int _hres, int _vres)
{
    hres = _hres;
    vres = _vres;

    // Array of RGBColor pointers
    colors = new RGBColor *[vres];

    // Assign RGBColor array to each element of pointer array
    for (int i = 0; i < hres; i++)
    {
        colors[i] = new RGBColor[hres];
    }
}
Image::Image(const ViewPlane &vp)
{
    hres = vp.get_hres();
    vres = vp.get_vres();

    // Array of RGBColor pointers
    colors = new RGBColor *[vres];

    // Assign RGBColor array to each element of pointer array
    for (int i = 0; i < hres; i++)
    {
        colors[i] = new RGBColor[hres];
    }
}

Image::~Image()
{
    // delete each of the RGBColor array
    for (int i = 0; i < hres; i++)
    {
        delete[] colors[i];
    }

    // delete RGBColor pointer array
    delete[] colors;
}

// Set pixel color. Convert to integer values.
void Image::set_pixel(int x, int y, const RGBColor &color)
{
    colors[x][y] = color;
}

// Set pixel color. Convert to integer values.
RGBColor Image::get_pixel(int x, int y)
{
    return colors[x][y];
}


// Write image to file in PPM format.
void Image::write_ppm(std::string path) const
{
    std::ofstream file;
    file.open (path);
    std::cout << path << std::endl;
    file << "P3\n";
    file << hres << " " << vres << "\n";
    file << "255\n";
    for (int y = 0; y < vres; ++y) {
        for (int x = 0; x < hres; ++x) {
            file << (int)(255* colors[x][y].r) << " " << 
                (int)(255* colors[x][y].g) << " " <<
                (int)(255* colors[x][y].b) << " ";
        }
        file << "\n";
    }
    file.close();
}
