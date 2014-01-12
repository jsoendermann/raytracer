#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"

typedef struct light {
    vector3 *pos;
} light;

light *make_light(vector3 *pos);

#endif
