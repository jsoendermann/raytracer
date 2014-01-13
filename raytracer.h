#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "colour.h"
#include "sphere.h"
#include "ray.h"
#include "light.h"


#define WIDTH 800
#define HEIGHT 800
#define SCREEN_DISTANCE 50.0

#define BG_COLOR_RED 0x0
#define BG_COLOR_GREEN 0x0
#define BG_COLOR_BLUE 0x50

// FIXME find a better name for this
#define SAME_SPHERE 1e-4

#define coords2index(x,y) ((y)*WIDTH+(x))
#define max(x,y) ((x)>(y)?(x):(y))


void find_closest_intersection_point(ray *r, sphere **spheres, int num_spheres,
        vector3 **closest_intersection_point, vector3 **surface_normal, sphere **intersected_sphere);
colour *trace(ray *r, sphere **spheres, int num_spheres, light **lights, int num_lights, const int recursion_depth);

int main(int argc, char **argv);
void write_image(colour **image);


#endif
