#ifndef COLOUR_H
#define COLOUR_H

typedef struct colour {
    char r;
    char g;
    char b;
} colour;

colour *make_colour(char r, char g, char b);

#endif
