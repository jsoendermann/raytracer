#ifndef SPHERE_H
#define SPHERE_H

#include "sphere.h"
#include "vector3.h"
#include "colour.h"

typedef struct sphere {
    vector3 *pos;
    double rad;

    colour *clr;
} sphere;

sphere *make_sphere(vector3 *pos, double rad, colour *clr);

void free_sphere(sphere *s);

#endif
