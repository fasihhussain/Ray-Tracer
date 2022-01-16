#pragma once
#include "Tracer.hpp"

#include <vector>


class Camera;
class Ray;
class Sampler;
class ShadeInfo;
class World;

class BasicTracer : public Tracer
{

public:
  // Constructors.
  BasicTracer() = default; // initialize members.

  // Destructor.
  ~BasicTracer()= default; // free memory.
  // Capture scene and save the image
  virtual Image* capture() const;
};
