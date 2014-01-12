#include <stdlib.h>

#include "sphere.h"

sphere *make_sphere(vector3 *pos, double rad) {
    sphere *s = (sphere*)malloc(sizeof(sphere));
    s->pos = pos;
    s->rad = rad;
    return s;
}

