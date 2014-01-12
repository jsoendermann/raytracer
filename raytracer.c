#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "raytracer.h"
#include "vector3.h"
#include "ray.h"
#include "sphere.h"
#include "colour.h"

colour *trace(ray *r, sphere **spheres, int num_spheres, const int recursion_depth) {
    colour *c;

    vector3 *closest_intersection_point = NULL;
    sphere *intersected_sphere = NULL;
    
    sphere *sphere;
    for (int i = 0; i < num_spheres; i++) {
        sphere = spheres[i];
        vector3 *sphere_intersection_point = intersect_sphere(r, sphere);
        if (sphere_intersection_point != NULL) {
            if (closest_intersection_point == NULL || distance(r->org, closest_intersection_point) < distance(r->org, sphere_intersection_point)) {
                closest_intersection_point = sphere_intersection_point;
                intersected_sphere = sphere;
            }
            else
                free(sphere_intersection_point);
        }
    }

    if (closest_intersection_point == NULL)
        return make_colour(BG_COLOR_RED, BG_COLOR_GREEN, BG_COLOR_BLUE);

    vector3 *intersection_normal = make_difference_vector(closest_intersection_point, sphere->pos);
    normalise(intersection_normal);

    if (closest_intersection_point == NULL)
        c = make_colour(255, 255, 255);
     else 
        c = make_colour(0,0,0);
    

    return c;
}

int main(int argc, char **argv) {
    sphere *spheres[] = {
        make_sphere(make_vect(-10, -10, -75-SCREEN_DISTANCE), 30, make_colour(255, 0, 0)),
        make_sphere(make_vect(20, 20, -100-SCREEN_DISTANCE), 40, make_colour(0, 255, 0))
    };

    int num_spheres = sizeof(spheres)/sizeof(spheres[0]);

    colour* image[WIDTH * HEIGHT];

    ray *r;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            r = make_ray(make_vect(0, 0, 0), make_normalised_vect(x-WIDTH/2, y-HEIGHT/2, -SCREEN_DISTANCE));

            image[coords2index(x,y)] = trace(r, spheres, num_spheres, 0);

            free_ray(r);
        }
    }

    for (int i = 0; i < num_spheres; i++)
        free_sphere(spheres[i]);

    write_image(image);
}

void write_image(colour **image) {
    char head[20];
    sprintf(head, "P6\n %d %d\n255\n", WIDTH, HEIGHT);

    FILE *f = fopen("image.ppm", "wb");
    if (!f) {
        printf("Unable to open file");
        exit(-1);
    }

    fwrite(head, sizeof(char), strlen(head), f);

    colour *c;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            c = image[coords2index(x,y)];
            fwrite(&c->r, sizeof(char), 1, f);
            fwrite(&c->g, sizeof(char), 1, f);
            fwrite(&c->b, sizeof(char), 1, f);
        }
    }

    fclose(f);
}

