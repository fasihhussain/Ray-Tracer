#pragma once
#include <vector>
#include "../geometry/Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
class BVHNode
{
private:
    int leaf;
    BVHNode *left;
    BVHNode *right;
    BBox bbox;

public:
    int lower;
    int upper;
    int depth;
    BVHNode() = default;
    BVHNode(int leaf, int lower, int upper,int depth);
    BVHNode &operator=(const BVHNode &other) = default;
    BVHNode(const BVHNode &other) = default;
    bool isLeaf() const; // return whether this node is a leaf
    void setBBox(BBox &bbox); // set the bounding box of this node
    BBox getBBox(); // get the bounding box of this node
    void setLeft(BVHNode *left); // set the left child of this node
    void setRight(BVHNode *right); // set the right child of this node
    BVHNode *getLeft(); // get the left child of this node
    BVHNode *getRight(); // get the right child of this node
    ~BVHNode();

    ShadeInfo hit_objects(ShadeInfo &shade_info, const Ray &ray, const std::vector<Geometry *> &geometries) const;
};

