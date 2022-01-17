# Ray Tracer (Fall 2021)

This project was a part of the course Computer Graphics (CS 440) offered by Dr. Waqar Saleem.

## Team Members
1. Khubaib Naeem
2. Shams Ul Arfeen
3. Fasih Hussain

## Website Link
https://habib-university.github.io/CG-team-vector-showcase/

## Description
This project extends the ray tracer previously developed in the course. It implements some of the ray tracing topics we have covered, namely:
- ray casting
- shading
- anti-aliasing
- light sources
- acceleration structures

The build files for all the scenes shown in the showcase are present in `/raytracer/build/`.

## Scenes
### Cherry Blossom Tree
![Cherry Blosson Tree](/Showcase/images/tree%20highres.png)

### House
![High Res House Scene](/Showcase/images/HouseScene.png)

## Features
- Acceleration Structures (`/raytracer/acceleration/`)
    * Bounding Volume Hierarchy
    * Uniform Grid
- Camera (`/raytracer/cameras/`)
    * Parallel
    * Perspective
- Geometry (`/raytracer/geometry`)
    * Triangles
    * Spheres
    * Smooth Triangles (For Smooth Shading)
- Lighting (`/raytracer/lights/`)
    * Point Light
    * Area Light
    * Directional Light
- Materials (`/raytracer/materials/`)
    * Cosine
    * Transparent
    * Shiny
    * Phong
- Shading
    * Flat Shading
    * Smooth Shading
    * Phong Shading
- Samplers (`/raytracer/samplers/`)
    * Simple Sampler
    * Regular Sampler
    * Random Sampler
    * Jittered Sampler
- Tracers (`/raytracer/tracers/`)
    * Recursive Tracer
    * Shadow Tracer
- Loading Mesh from Stanford PLY Files
- Multi-threading

## Acceleration Structures
### Uniform Grid
|                    | Without Grid (Time)(seconds) | Without Grid (RAM Usage)(KB) | With Grid (Time)(seconds) | With Grid (RAM Usage)(KB) |
|:------------------:|:----------------------------:|:----------------------------:|:-------------------------:|:-------------------------:|
|  1,000 primitives  |             6.946            |             8,136            |            0.41           |           8,452           |
|  10,000 primitives |            66.792            |             8,704            |           0.512           |           13,284          |
|  20,000 primitives |            133.622           |             9,236            |           0.535           |           12,412          |
|  40,000 primitives |            266.496           |            10,936            |           0.629           |           17,356          |
| 100,000 primitives |             ~3600            |            14,447            |           0.817           |           32,008          |


## Samplers
### Simple Sample (Baseline)
![Simple Sampler](/Showcase/images/Simple.jpeg)

### Regular Sampler (Anti-Aliasing)
![Regular Sampler](/Showcase/images/Regular.jpeg)

### Random Sampler (Anti-Aliasing)
![Random Sampler](/Showcase/images/Random.jpeg)

### Jittered Sampler (Anti-Aliasing)
![Jittered Sampler](/Showcase/images/Jittered.jpeg)

## Shading
### Flat Shading
![Flat Shading](/Showcase/images/Flat%20Shading.jpeg)

### Smooth Shading
![Smooth Shading](/Showcase/images/Smooth%20Shading.jpeg)

### Phong Shading
![Phong Shading](/Showcase/images/LowResScene.png)

## Materials and Lighting
### Shiny, Glass and Transparent Material\*
![Shiny, Glass and Transparent Material](/Showcase/images/Shiny,Glass,Transparent.png)

### Point Light
![Point Light](/Showcase/images/Point%20Light.png)

### Directional Light
![Directional Light](/Showcase/images/DirectionalLightRecursive.png)

### Area Light
![Area Light](/Showcase/images/AreaLight.png)

## Tracers
### Recursive Tracer
![Recursive Tracer](/Showcase/images/DirectionalLightRecursive.png)

### Shadow Tracer
![Shadow Tracer](/Showcase/images/DirectionalLightShadow.png)

## Acknowledgements
- Ray Tracing from the Ground Up
- Wikipedia (Shading Articles)
- Ray Tracing in One Weekend
- [House Model](https://free3d.com/3d-model/house-61304.html)
- [Cherry Blossom Tree Model](https://www.turbosquid.com/3d-models/xfrogplants-weeping-cherry-prunus-pendula-3d-model-1737617)
- [Grass Model](https://www.cgtrader.com/free-3d-models/plant/grass/green-lawn-8d4341d7-6281-40e9-8872-d429512a3b3b)
- [HapPLY](https://www.cgtrader.com/free-3d-models/plant/grass/green-lawn-8d4341d7-6281-40e9-8872-d429512a3b3b)
- [Bunny Mesh](http://graphics.stanford.edu/data/3Dscanrep/?)
