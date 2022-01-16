#pragma once

/**
   This file declares the Simple class which represents a simple sampler.

   It shoots a single ray of weight 1 through a pixel.

   Courtesy Kevin Suffern.
*/

#include "Sampler.hpp"

class RandomSampler : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().
  int n;
public:
  // Constructors.
  RandomSampler();                      // initializes members to NULL.
  RandomSampler(int);
  RandomSampler(Camera *c_ptr, ViewPlane *v_ptr,int n); // set members.

  // Copy constuctor and assignment operator.
  RandomSampler(const RandomSampler &camera);
  RandomSampler &operator=(const RandomSampler &other);

  // Desctructor.
  virtual ~RandomSampler() = default;

  // Shoot n^2 rays of weight 1/n^2 through the pixel, randomly.
  std::vector<Ray> get_rays(int px, int py) const override;
};
