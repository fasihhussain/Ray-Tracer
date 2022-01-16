#pragma once
#include "Geometry.hpp"
#include <vector>
class Compound : public Geometry
{
protected:
    std::vector<Geometry *> objects;

public:
    Compound();
    Compound(const Compound &object);
    Compound &operator=(const Compound &rhs);
    Compound(std::vector<Geometry *> objects);
    void add_object(Geometry *object);
    virtual ~Compound();
    virtual bool hit(const Ray &ray, float &t, ShadeInfo &sinfo) const;
    virtual BBox getBBox() const;
    virtual std::string to_string() const;

    // TODO: Implement shadow_hit?
};