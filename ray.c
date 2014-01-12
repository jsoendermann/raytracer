#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "ray.h"
#include "sphere.h"

#define EPSILON 0.01

ray *make_ray(vector3 *org, vector3 *dir) {
    ray *r = (ray*)malloc(sizeof(ray));
    r->org = org;
    r->dir = dir;
    if (abs(vector_length(dir) - 1.0) > EPSILON) {
        printf("Non-normalised vector as direction! Len: %.2f\n", vector_length(dir));
        exit(-1);
    }
    return r;
}

ray *copy_ray(const ray *r) {
    ray *new = (ray*)malloc(sizeof(ray));
    new->org = copy_vector(r->org);
    new->dir = copy_vector(r->dir);
    return new;
}

void free_ray(ray *r) {
    free(r->org);
    free(r->dir);
    free(r);
}

vector3 *intersect_sphere(const ray *r_org, const sphere *s) {
    ray *r = copy_ray(r_org);

    vector3 *transf_to_sphere_org = copy_vector(s->pos);
    invert(transf_to_sphere_org);
    
    shift(r->org, transf_to_sphere_org);

    free(transf_to_sphere_org);

    double A = square(r->dir->x) + square(r->dir->y) + square(r->dir->z);
    double B = 2 * (r->dir->x * r->org->x + r->dir->y * r->org->y + r->dir->z * r->org->z);
    double C = square(r->org->x) + square(r->org->y) + square(r->org->z) - square(s->rad);

    double discriminant = square(B) - 4 * A * C;

    if (discriminant < 0.0) {
        free_ray(r);
        return NULL;
    }

    double q;
    if (B < 0)
        q = -0.5 * (B - sqrt(discriminant));
    else
        q = -0.5 * (B + sqrt(discriminant));
    
    double t0 = q / A;
    double t1 = C / q;

    if (t0 < 0)
        t0 = t1;

    vector3 *intersect_point = copy_vector(r->org);
    mix_vectors(intersect_point, r->dir, t0);

    vector3 *transf_back_to_view_coords = copy_vector(s->pos);
    

    shift(intersect_point, transf_back_to_view_coords);

    free(transf_back_to_view_coords);
    free_ray(r);


    return intersect_point;
}

