#include "ShadeInfo.hpp"

// Constructor.
ShadeInfo::ShadeInfo(const World &wr)
{
    hit = false;
    t = kHugeValue;
    w = &wr;
}