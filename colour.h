#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

static int colour_max_id = 0;

typedef struct colour {
    int id;

    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour;

colour *make_colour(uint8_t r, uint8_t g, uint8_t b);
colour *copy_colour(colour *c);

void add_colour(colour *c1, const colour *c2);
// FIXME find a better name for this
void mult(colour *c1, double f);

char *colour_to_string(colour *c);
void print_colour(colour *c);


#endif
