#include <stdlib.h>

#include "sphere.h"

sphere *make_sphere(vector3 *pos, double rad, colour *clr) {
    sphere *s = (sphere*)malloc(sizeof(sphere));
    s->pos = pos;
    s->rad = rad;
    s->clr = clr;
    s->id = spheres_max_id++;
    return s;
}

void free_sphere(sphere *s) {
    free(s->clr);
    free(s);
}
