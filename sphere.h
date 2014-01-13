#ifndef SPHERE_H
#define SPHERE_H

#include "sphere.h"
#include "vector3.h"
#include "colour.h"

static int spheres_max_id = 0;

typedef struct sphere {
    int id;
    
    vector3 *pos;
    double rad;

    colour *clr;
} sphere;

sphere *make_sphere(vector3 *pos, double rad, colour *clr);

void free_sphere(sphere *s);

#endif
