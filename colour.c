#include <stdlib.h>

#include "colour.h"

colour *make_colour(char r, char g, char b) {
    colour *c = (colour*)malloc(sizeof(colour));
    c->r = r;
    c->g = g;
    c->b = b;
    return c;
}
