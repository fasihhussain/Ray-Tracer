#include "BVHNode.hpp"
#include <iostream>
BVHNode::BVHNode(int leaf, int lower, int upper,int depth) : leaf(leaf), lower(lower), upper(upper), depth(depth)
{
}

bool BVHNode::isLeaf() const
{
    return leaf == 1;
}
ShadeInfo BVHNode::hit_objects(ShadeInfo &shade_info, const Ray &ray, const std::vector<Geometry *> &geometries) const
{
    // If not a leaf node, don't do anything and return our initial shade_info
    if (leaf == 0) {
        return shade_info;
    }
    // If leaf node, hit every object in the leaf node
    for (int i = lower; i < upper; i++)
    {
        geometries[i]->hit(ray, shade_info.t, shade_info);
    }
    return shade_info;
}


void BVHNode::setBBox(BBox &bbox)
{
    this->bbox = bbox;
}

BBox BVHNode::getBBox()
{
    return bbox;
}

void BVHNode::setLeft(BVHNode *left)
{
    this->left = left;
} 

void BVHNode::setRight(BVHNode *right)
{
    this->right = right;
}

BVHNode::~BVHNode()
{
    // If the left child is not null, delete it
    if (left) {
        delete left;
    }
    // If the right child is not null, delete it
    if (right) {
        delete right;
    }
}

BVHNode* BVHNode::getLeft()
{
    return left;
}

BVHNode* BVHNode::getRight()
{
    return right;
}