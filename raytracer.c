#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "raytracer.h"
#include "vector3.h"
#include "ray.h"
#include "sphere.h"
#include "colour.h"

colour *trace(ray *r, sphere **spheres, const int recursion_depth) {
    colour *c = make_colour(0,0,0);

    for (int i = 0; i < 1; i++) {
        vector3 *intersect = intersect_sphere(r, spheres[i]);
        if (intersect != NULL)
            c = make_colour(255,255,255);
    }
    return c;
}

int main(int argc, char **argv) {
    sphere *spheres[] = {
        //make_sphere(make_vect(0, 0, -10-SCREEN_DISTANCE), 300),
        make_sphere(make_vect(0, 0, -50-SCREEN_DISTANCE), 40)
    };

    colour* image[WIDTH * HEIGHT];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            ray *r = make_ray(make_vect(0, 0, 0), make_normalised_vect(x-WIDTH/2, y-HEIGHT/2, -SCREEN_DISTANCE));

            image[x*y] = trace(r, spheres, 0);

            free_ray(r);
        }
    }
    write_image(image);
}

void write_image(colour **image) {
    char *head = "P6\n50 50\n255\n";
    FILE *f = fopen("image.ppm", "wb");
    if (!f) {
        printf("Unable to open file");
        exit(-1);
    }
    fwrite(head, sizeof(char), strlen(head), f);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fwrite(&image[x*y]->r, sizeof(char), 1, f);
            fwrite(&image[x*y]->g, sizeof(char), 1, f);
            fwrite(&image[x*y]->b, sizeof(char), 1, f);
        }
    }
}

