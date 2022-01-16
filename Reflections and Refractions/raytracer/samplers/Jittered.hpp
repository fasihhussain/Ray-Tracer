#pragma once

/**
   This file declares the Simple class which represents a simple sampler.

   It shoots a single ray of weight 1 through a pixel.

   Courtesy Kevin Suffern.
*/

#include "Sampler.hpp"

class Jittered : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().
  int n;
public:
  // Constructors.
  Jittered();                      // initializes members to NULL.
  Jittered(int);
  Jittered(Camera *c_ptr, ViewPlane *v_ptr,int n); // set members.

  // Copy constuctor and assignment operator.
  Jittered(const Jittered &camera);
  Jittered &operator=(const Jittered &other);

  // Desctructor.
  virtual ~Jittered() = default;

  // Shoot a ray of weight 1 through the center of the pixel.
  std::vector<Ray> get_rays(int px, int py) const override;
};
