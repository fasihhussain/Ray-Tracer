#pragma once
#include "Acceleration.hpp"
#include <vector>
#include "../geometry/Compund.hpp"
#include "../utilities/BBox.hpp"
class Grid : public Acceleration
{
public:
    Grid(std::vector<Geometry *>&);
    Grid(const Grid &);
    virtual ~Grid();
    Grid &operator=(const Grid &);
    void setup_cells();
    virtual ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade_info) const ;

private:
    std::vector<Geometry *> primitives;
    std::vector<Compound *> cells;
    // Number of cells in each dimension
    int nx,ny,nz;
    // Bounding box of the grid
    BBox bbox;
    // Static function to clamp index values in [0, n-1]
    static float clamp(float c, float min, float max);
    
};