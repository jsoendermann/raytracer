#include <stdlib.h>

#include "light.h"

light *make_light(vector3 *pos) {
    light *l = (light*)malloc(sizeof(light));
    l->pos = pos;
    return l;
}
