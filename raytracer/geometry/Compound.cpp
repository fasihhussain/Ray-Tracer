#include "Compund.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"
#include <sstream>

Compound::Compound() : Geometry()
{
    if (objects.size() > 0)
    {
        objects.clear();
    }
}

Compound::Compound(const Compound &c) : Geometry(c)
{
    // empty objects
    if (objects.size() > 0)
    {
        objects.clear();
    }
    if (c.objects.size() > 0)
    {
        for (int i = 0; i < c.objects.size(); i++)
        {
            objects.push_back(c.objects[i]);
        }
    }
}

Compound &Compound::operator=(const Compound &c)
{
    if (this == &c)
        return *this;
    Geometry::operator=(c);
    // add all objects
    if (c.objects.size() > 0)
    {
        for (int i = 0; i < c.objects.size(); i++)
        {
            objects.push_back(c.objects[i]);
        }
    }
    return *this;
}

Compound::~Compound()
{
    // Go over all objects and delete them
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

void Compound::add_object(Geometry *object)
{
    objects.push_back(object);
}

bool Compound::hit(const Ray &ray, float &t, ShadeInfo &shade_info) const
{
    // Iterate over everything
    bool hit_anything = false;
    for (int i = 0; i < objects.size(); i++)
    {
        hit_anything |= objects[i]->hit(ray, t, shade_info);
    }
    return hit_anything;
}

BBox Compound::getBBox() const
{
    BBox bbox;
    for (int i = 0; i < objects.size(); i++)
    {
        bbox.extend(objects[i]->getBBox());
    }
    return bbox;
}

std::string Compound::to_string() const
{
    std::stringstream ss;
    ss << "Compound: " << std::endl;
    for (int i = 0; i < objects.size(); i++)
    {
        ss << objects[i]->to_string() << "\n";
    }
    ss << "End Compound\n";
    return ss.str();
}