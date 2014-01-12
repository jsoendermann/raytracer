#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "colour.h"
#include "sphere.h"
#include "ray.h"


#define WIDTH 50
#define HEIGHT 50
#define SCREEN_DISTANCE 50.0

#define BG_COLOR_RED 20
#define BG_COLOR_GREEN 20
#define BG_COLOR_BLUE 20


#define coords2index(x,y) ((y)*WIDTH+(x))


colour *trace(ray *r, sphere **spheres, int num_spheres, const int recursion_depth);
int main(int argc, char **argv);
void write_image(colour **image);


#endif
