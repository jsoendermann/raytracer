#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 640
#define HEIGHT 480
#define SCREEN_DISTANCE 20.0

#define square(x) ((x)*(x))
#define min(x,y) ((x)<(y)?(x):(y))

#define EPSILON 0.01

typedef struct vector3 {
    double x;
    double y;
    double z;
} vector3;

double vector_length(vector3 *v) {
    return sqrt(square(v->x) + square(v->y) + square(v->z));
}

void normalise(vector3 *v) {
    double length = vector_length(v);

    v->x /= length;
    v->y /= length;
    v->z /= length;
}


vector3 *make_vect(double x, double y, double z) {
    vector3 *v = (vector3*)malloc(sizeof(vector3));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

vector3 *make_normalised_vect(double x, double y, double z) {
    vector3 *v = make_vect(x, y, z);
    normalise(v);
    return v;
}

double distance(vector3 *v1, vector3 *v2) {
    return sqrt(square(v1->x - v2->x) + square(v1->y - v2->y) + square(v1->z - v2->z));
}

void scale(vector3 *v, double s) {
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

void shift(vector3 *v1, const vector3 *v2) {
    v1->x += v2->x;
    v1->y += v2->y;
    v1->z += v2->z;
}

void invert(vector3 *v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void mix_vectors(vector3 *v1, const vector3 *v2, double t) {
    v1->x += t * v2->x;
    v1->y += t * v2->y;
    v1->z += t * v2->z;
}

vector3 *copy_vector(vector3 *v) {
    vector3 *new = (vector3*)malloc(sizeof(vector3));
    memcpy(new, v, sizeof(vector3));
    return new;
}

char *vector_to_string(vector3 *v) {
    char *s = (char*)malloc(sizeof(char)*25);
    sprintf(s, "<%.2f, %.2f, %.2f>", v->x, v->y, v->z);
    return s;
}

void print_vector(vector3 *v) {
    char *s = vector_to_string(v);
    printf("%s\n", s);
    free(s);
}

typedef struct colour {
    float r;
    float g;
    float b;
} colour;

colour *make_colour(float r, float g, float b) {
    colour *c = (colour*)malloc(sizeof(colour));
    c->r = r;
    c->g = g;
    c->b = b;
    return c;
}

typedef struct ray {
    vector3 *org;
    vector3 *dir;
} ray;

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

void free_ray(ray *r) {
    free(r->org);
    free(r->dir);
    free(r);
}

ray *copy_ray(const ray *r) {
    ray *new = (ray*)malloc(sizeof(ray));
    new->org = copy_vector(r->org);
    new->dir = copy_vector(r->dir);
    return new;
}

typedef struct sphere {
    vector3 *pos;
    double rad;
} sphere;

sphere *make_sphere(vector3 *pos, double rad) {
    sphere *s = (sphere*)malloc(sizeof(sphere));
    s->pos = pos;
    s->rad = rad;
    return s;
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
    
    double t0 = (-B - sqrt(discriminant)) / (2.0 * A);
    double t1 = (B - sqrt(discriminant)) / (2.0 * A);

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


colour *trace(ray *r, const int recursion_depth) {
    colour *c = make_colour(0,0,0);
    return c;
}

int main(int argc, char **argv) {
    sphere *spheres[] = {
        make_sphere(make_vect(0, 0, -10), 3),
        make_sphere(make_vect(5, 5, -12), 4)
    };

    colour* image[WIDTH * HEIGHT];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            ray *r = make_ray(make_vect(0, 0, 0), make_normalised_vect(x, y, -SCREEN_DISTANCE));

            image[x*y] = trace(r, 0);

            free_ray(r);
        }
    }
}
