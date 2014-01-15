#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "vector3.h"

vector3 *make_vector(double x, double y, double z) {
    vector3 *v = (vector3*)malloc(sizeof(vector3));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

vector3 *make_normalised_vector(double x, double y, double z) {
    vector3 *v = make_vector(x, y, z);
    normalise(v);
    return v;
}

vector3 *copy_vector(vector3 *v) {
    vector3 *new = (vector3*)malloc(sizeof(vector3));
    memcpy(new, v, sizeof(vector3));
    return new;
}

vector3 *make_difference_vector(vector3 *v1, vector3 *v2) {
    return make_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}


void normalise(vector3 *v) {
    double length = vector_length(v);

    v->x /= length;
    v->y /= length;
    v->z /= length;
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

double vector_length(vector3 *v) {
    return sqrt(square(v->x) + square(v->y) + square(v->z));
}


double distance(vector3 *v1, vector3 *v2) {
    return sqrt(square(v1->x - v2->x) + square(v1->y - v2->y) + square(v1->z - v2->z));
}

double dot_product(vector3 *v1, vector3 *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
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
