#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "colour.h"

#define min(x,y) ((x)<(y)?(x):(y))

colour *make_colour(uint8_t r, uint8_t g, uint8_t b) {
    colour *c = (colour*)malloc(sizeof(colour));
    c->r = r;
    c->g = g;
    c->b = b;
    c->id = colour_max_id++;
    return c;
}

colour *copy_colour(colour *c) {
    colour *new = (colour*)malloc(sizeof(colour));
    memcpy(new, c, sizeof(colour));
    return new;
}

void add_colour(colour *c1, const colour *c2) {
    c1->r = min(c1->r + c2->r, 255);
    c1->g = min(c1->g + c2->g, 255);
    c1->b = min(c1->b + c2->b, 255);
}

void mult(colour *c1, double f) {
    c1->r = min(c1->r * f, 255);
    c1->g = min(c1->g * f, 255);
    c1->b = min(c1->b * f, 255);
}

char *colour_to_string(colour *c) {
    char *s = (char*)malloc(sizeof(char)*25);
    sprintf(s, "<%d, %d, %d>", c->r, c->g, c->b);
    return s;
}

void print_colour(colour *c) {
    char *s = colour_to_string(c);
    printf("%s\n", s);
    free(s);
}
