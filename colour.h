#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

static int max_id = 0;

typedef struct colour {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    int id;
} colour;

colour *make_colour(uint8_t r, uint8_t g, uint8_t b);

char *colour_to_string(colour *c);
void print_colour(colour *c);


#endif
