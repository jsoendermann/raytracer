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

// this function returns the intersection point of r_org and s
// if there is one, NULL otherwise
vector3 *intersect_sphere(const ray *r_org, const sphere *s) {
    ray *r = copy_ray(r_org);

    // transfer r to object space
    vector3 *transf_to_sphere_org = copy_vector(s->pos);
    invert(transf_to_sphere_org);
    shift(r->org, transf_to_sphere_org);
    free(transf_to_sphere_org);

    double A = dot_product(r->dir, r->dir);
    double B = 2 * dot_product(r->dir, r->org);
    double C = dot_product(r->org, r->org) - square(s->rad);

    double discriminant = square(B) - 4 * A * C;

    if (discriminant < 0.0) {
        free_ray(r);
        return NULL;
    }

    double t0 = (-B - sqrt(discriminant)) / (2.0 * A);
    double t1 = (B - sqrt(discriminant)) / (2.0 * A);


    if (t0 < 0 && t1 < 0) 
        return NULL;
    else if (t0 < 0 || t1 < 0)
        t0 = max(t0, t1);
    else //(t0 >= 0 && t1 >= 0)
        t0 = min(t0, t1);


    vector3 *intersect_point = copy_vector(r_org->org);
    mix_vectors(intersect_point, r->dir, t0);

    free_ray(r);


    return intersect_point;
}

char *ray_to_string(ray *r)  {
    char *v1 = vector_to_string(r->org);
    char *v2 = vector_to_string(r->dir);

    char *s = (char*)malloc(sizeof(char)*70);
    sprintf(s, "<org:%s dir:%s>", v1, v2);

    free(v1);
    free(v2);

    return s;
}

void print_ray(ray *r) {
    char *s = ray_to_string(r);
    printf("%s\n", s);
    free(s);
}
