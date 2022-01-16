#include "BVH.hpp"
#include <map>
#include <algorithm>
#include <iostream>
BVHTree::BVHTree(std::vector<Geometry *> &geometries)
{
    primitives = geometries;
    root = nullptr;
    std::cout << "Primitives created of size " << primitives.size() << std::endl;
    build_tree();
}
void BVHTree::build_tree()
{
    std::cout << "Building tree with nodes " << primitives.size() << std::endl;
    // If <=4 nodes, the root node we have is a leaf node
    if (primitives.size() <= 3)
    {
        this->root = new BVHNode(1, 0, primitives.size(), 0);
        std::cout << "Root created of size " << primitives.size() << std::endl;
        return;
    }
    // Else create a stack for node pointers
    std::vector<BVHNode *> stack;
    // Create map between Geometry* and bbox
    std::map<Geometry *, BBox> bbox_map;

    // Go over each primitive and create a bbox for it
    for (int i = 0; i < primitives.size(); i++)
    {
        bbox_map[primitives[i]] = primitives[i]->getBBox();
    }

    // Create a non-leaf root node

    root = new BVHNode(0, 0, primitives.size(), 0);

    BBox current_bbox;
    // Compute the box for the root node
    for (int i = 0; i < primitives.size(); i++)
    {
        // Add the primitive to the node
        current_bbox.extend(primitives[i]->getBBox());
        
    }
    root->setBBox(current_bbox);

    // Push the root to the stack
    stack.push_back(root);
    // While the stack is not empty
    while (!stack.empty())
    {
        // Pop the top node from the stack
        BVHNode *node = stack.back();
        stack.pop_back();
        // find out which primitives are within the node
        // [lower,upper) of primitives
        int lower = node->lower;
        int upper = node->upper;
        // Find the longest axis
        Vector3D difference = current_bbox.pmax - current_bbox.pmin;
        int axis = difference.max_absolute_axis();

        // Decide to put half the primitives in the left or right node
        int split_index = (lower + upper) / 2;
        // std::cout << "NEEEEd" << std::endl;
        // Create a partition based on axis
        // Sort the primitives based on the axis chosen
        // such the primitives based on their axis, such that 
        // everything to left of nth element is smaller
        // and everything to the right is larger
        std::nth_element(primitives.begin() + lower, primitives.begin() + split_index, primitives.begin() + upper, [axis](Geometry *a, Geometry *b)
                         {
                             BBox a_box = a->getBBox();
                             Point3D a_avg = (a_box.pmin + a_box.pmax) * 0.5;
                             BBox b_box = b->getBBox();
                             Point3D b_avg = (b_box.pmin + b_box.pmax) * 0.5;
                             if (axis == 0)
                             {
                                 return a_avg.x < b_avg.x;
                             }
                             else if (axis == 1)
                             {
                                 return a_avg.y < b_avg.y;
                             }
                             else
                             {
                                 return a_avg.z < b_avg.z;
                             }
                         });
        // Create a new node
        bool is_leaf_left = (split_index - lower) <= 3;
        // || (split_index - lower) == primitives.size();
        bool is_leaf_right = (upper - split_index) <= 3;
        // || (upper - split_index) == primitives.size();
        BVHNode *left = new BVHNode(is_leaf_left, lower, split_index, node->depth + 1);
        BVHNode *right = new BVHNode(is_leaf_right, split_index, upper, node->depth + 1);
        // Set the bbox of the new node
        if (!is_leaf_left)
        {
            BBox left_bbox;
            // std::cout << "Left node is not leaf" << std::endl;
            for (int i = lower; i < split_index; i++)
            {
                left_bbox.extend(primitives[i]->getBBox());
            }
            left->setBBox(left_bbox);
            // Push the left node to the stack
            stack.push_back(left);
        }

        if (!is_leaf_right)
        {
            BBox right_bbox;
            for (int i = split_index; i < upper; i++)
            {
                right_bbox.extend(primitives[i]->getBBox());
            }
            right->setBBox(right_bbox);
            // Push the right node to the stack
            stack.push_back(right);
        }
        // Set the children of the node
        node->setLeft(left);
        node->setRight(right);
    }
    std::cout << "Tree built" << std::endl;
}

ShadeInfo BVHTree::hit_objects(const Ray &ray, ShadeInfo &shade_info) const
{

    // If no root, do nothing
    if (root == nullptr)
    {
        return shade_info;
    }

    BVHNode *node = root;

    // create a stack for node pointers
    std::vector<BVHNode *> stack;
    // push the root to the stack
    stack.push_back(node);
    // while the stack is not empty
    while (!stack.empty())
    {
        // pop the top node
        node = stack.back();
        stack.pop_back();
        // if the node is a leaf
        if (node->isLeaf())
        {
            // std::cout << "Leaf node" << std::endl;
            node->hit_objects(shade_info, ray, primitives);
        }
        else
        {
            BVHNode *left = node->getLeft();
            BVHNode *right = node->getRight();
            float t_in = 0;
            float t_out = 0;


            if (node->getBBox().hit(ray, t_in, t_out))
            {
                if (left)
                {
                    stack.push_back(left);
                }
                if (right)
                {
                    stack.push_back(right);
                }
            }
        }
    }
    return shade_info;
}

BVHTree::~BVHTree()
{
    // Delete the root node which recursively would delete the other nodes made
    if (root)
    {
        delete root;
    }
}