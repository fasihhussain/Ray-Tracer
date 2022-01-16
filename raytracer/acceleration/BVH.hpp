#pragma once
#include "Acceleration.hpp"
#include "../geometry/Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "BVHNode.hpp"
class BVHTree : public Acceleration
{
private:
    std::vector<Geometry *> primitives;
    BVHNode *root;

public:
    BVHTree(std::vector<Geometry *> &geometries);
    // Hit objects in the world with a ray.
    ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade_info) const;
    void build_tree(); // construct all the nodes for the tree
    ~BVHTree();
};