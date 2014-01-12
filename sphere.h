#ifndef SPHERE_H
#define SPHERE_H

#include "sphere.h"
#include "vector3.h"

typedef struct sphere {
    vector3 *pos;
    double rad;
} sphere;

sphere *make_sphere(vector3 *pos, double rad);

#endif
