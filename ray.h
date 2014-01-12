#ifndef RAY_H
#define RAY_H

#include "vector3.h"
#include "sphere.h"

typedef struct ray {
    vector3 *org;
    vector3 *dir;
} ray;

ray *make_ray(vector3 *org, vector3 *dir);
ray *copy_ray(const ray *r);
void free_ray(ray *r);

vector3 *intersect_sphere(const ray *r_org, const sphere *s);

char *ray_to_string(ray *r);
void print_ray(ray *r);

#endif
