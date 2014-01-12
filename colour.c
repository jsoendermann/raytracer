#include <stdlib.h>
#include <stdio.h>

#include "colour.h"

colour *make_colour(uint8_t r, uint8_t g, uint8_t b) {
    colour *c = (colour*)malloc(sizeof(colour));
    c->r = r;
    c->g = g;
    c->b = b;
    c->id = max_id++;
    return c;
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
