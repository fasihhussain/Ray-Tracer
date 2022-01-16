#include "Grid.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>

Grid::Grid(std::vector<Geometry *> &geom)
{
    // Set the primitives vector and then cells
    primitives = geom;
    setup_cells();
}

Grid::Grid(const Grid &other)
{
    // Copy everything from other
    primitives = other.primitives;
    cells = other.cells;
    nx = other.nx;
    ny = other.ny;
    nz = other.nz;
}

Grid &Grid::operator=(const Grid &other)
{
    if (this != &other)
    {
        primitives = other.primitives;
        cells = other.cells;
        nx = other.nx;
        ny = other.ny;
        nz = other.nz;
    }
    return *this;
}

float Grid::clamp(float c, float min, float max)
{
    if (c < min)
        return min;
    if (c > max)
        return max;
    return c;
}

Grid::~Grid()
{
    for (auto &cell : cells)
        delete cell;
}
// Adapted from Ray Tracing from the Ground Up Chapter 22
void Grid::setup_cells()
{
    // Find the bounding box of the scene
    for (Geometry *&primitive : primitives)
    {
        bbox.extend(primitive->getBBox());
    }
    // based on that, compute minimum and maximum point of the grid
    Point3D p0 = bbox.pmin;
    Point3D p1 = bbox.pmax;
    // Compute the number of cells in each dimension
    float wx = p1.x - p0.x;
    float wy = p1.y - p0.y;
    float wz = p1.z - p0.z;
    float multiplier = 2.0;
    float s = std::pow((wx * wy * wz) / primitives.size(), 1.0 / 3.0);
    nx = multiplier * wx / s + 1;
    ny = multiplier * wy / s + 1;
    nz = multiplier * wz / s + 1;

    // Reserve the memory for the cells
    cells.reserve(nx * ny * nz);
    // Initialize the cells
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                cells.push_back(nullptr);
            }
        }
    }
    for (Geometry *&primitive : primitives)
    {
        // Find the Bounding box of the primitive
        BBox bbox_prim = primitive->getBBox();
        // and hence the min and max point
        Point3D bboxMin = bbox_prim.pmin;
        Point3D bboxMax = bbox_prim.pmax;
        // Use that to find the cell indices
        int ixmin = clamp((bboxMin.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
        int ixmax = clamp((bboxMax.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
        int iymin = clamp((bboxMin.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
        int iymax = clamp((bboxMax.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
        int izmin = clamp((bboxMin.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
        int izmax = clamp((bboxMax.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

        // Based on the cell indices, add the primitive to the cells
        for (int ix = ixmin; ix <= ixmax; ix++)
        {
            for (int iy = iymin; iy <= iymax; iy++)
            {
                for (int iz = izmin; iz <= izmax; iz++)
                {
                    int index = ix + nx * (iy + ny * iz);

                    // If initially no primitives,
                    // add a pointer to Compound/Geometry list
                    // else add the primitive to the list
                    if (cells[index] == nullptr)
                    {
                        cells[index] = new Compound();
                    }
                    cells[index]->add_object(primitive);
                }
            }
        }
    }
}

ShadeInfo Grid::hit_objects(const Ray &ray, ShadeInfo &shade_info) const
{
    int ix, iy, iz;
    float tmin, tmax, tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;
    // If we don't lie in the grid, return the shade info as it is
    if (!bbox.hit(ray, tmin, tmax, tx_min, tx_max, ty_min, ty_max, tz_min, tz_max))
    {
        return shade_info;
    }
    // If our ray starts inside the grid, we need to find the indices where it starts from
    if (bbox.contains(ray.o))
    {
        ix = clamp((ray.o.x - bbox.pmin.x) * nx / (bbox.pmax.x - bbox.pmin.x), 0, nx - 1);
        iy = clamp((ray.o.y - bbox.pmin.y) * ny / (bbox.pmax.y - bbox.pmin.y), 0, ny - 1);
        iz = clamp((ray.o.z - bbox.pmin.z) * nz / (bbox.pmax.z - bbox.pmin.z), 0, nz - 1);
    }
    else
    {
        // Compute the indices of the cell where the ray will first hit the box
        Point3D p = ray.o + ray.d * tmin;
        ix = clamp((p.x - bbox.pmin.x) * nx / (bbox.pmax.x - bbox.pmin.x), 0, nx - 1);
        iy = clamp((p.y - bbox.pmin.y) * ny / (bbox.pmax.y - bbox.pmin.y), 0, ny - 1);
        iz = clamp((p.z - bbox.pmin.z) * nz / (bbox.pmax.z - bbox.pmin.z), 0, nz - 1);
    }

    // Setup 3D DDA parameters
    float dtx = (tx_max - tx_min) / nx;
    float dty = (ty_max - ty_min) / ny;
    float dtz = (tz_max - tz_min) / nz;

    float tx_next, ty_next, tz_next;
    int ix_step, iy_step, iz_step;
    int ix_stop, iy_stop, iz_stop;

    if (ray.d.x > 0)
    {
        tx_next = tx_min + (ix + 1) * dtx;
        ix_step = 1;
        ix_stop = nx;
    }
    else
    {
        tx_next = tx_min + (nx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }

    if (ray.d.x == 0)
    {
        tx_next = kHugeValue;
    }

    if (ray.d.y > 0)
    {
        ty_next = ty_min + (iy + 1) * dty;
        iy_step = 1;
        iy_stop = ny;
    }
    else
    {
        ty_next = ty_min + (ny - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }

    if (ray.d.y == 0)
    {
        ty_next = kHugeValue;
    }

    if (ray.d.z > 0)
    {
        tz_next = tz_min + (iz + 1) * dtz;
        iz_step = 1;
        iz_stop = nz;
    }
    else
    {
        tz_next = tz_min + (nz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }

    if (ray.d.z == 0)
    {
        tz_next = kHugeValue;
    }

    while (true)
    {
        // Perform 3D DDA
        Compound *cell = cells[ix + nx * (iy + ny * iz)];
        if (tx_next < ty_next && tx_next < tz_next)
        {
            // If there is a cell, check if there is a hit
            // If there is WITHIN THE CELL, end process and return the shade info
            if (cell && cell->hit(ray, shade_info.t, shade_info) && shade_info.t < tx_next)
            {
                return shade_info;
            }
            // Move forward
            ix += ix_step;
            tx_next += dtx;
            // If we reach the end of the grid, end process and return the shade info
            if (ix == ix_stop)
            {
                return shade_info;
            }
        }
        else
        {
            if (ty_next < tz_next)
            {
                // If there is a cell, check if there is a hit
                // If there is WITHIN THE CELL, end process and return the shade info
                if (cell && cell->hit(ray, shade_info.t, shade_info) && shade_info.t < ty_next)
                {
                    return shade_info;
                }
                // Move forward
                iy += iy_step;
                ty_next += dty;
                // If we reach the end of the grid, end process and return the shade info
                if (iy == iy_stop)
                {
                    return shade_info;
                }
            }
            else
            {
                // If there is a cell, check if there is a hit
                // If there is WITHIN THE CELL, end process and return the shade info
                if (cell && cell->hit(ray, shade_info.t, shade_info))
                {
                    return shade_info;
                }
                // Move forward
                iz += iz_step;
                tz_next += dtz;
                // If we reach the end of the grid, end process and return the shade info
                if (iz == iz_stop)
                {
                    return shade_info;
                }
            }
        }
    }
    return shade_info;
}
