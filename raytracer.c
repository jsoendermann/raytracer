#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "raytracer.h"
#include "vector3.h"
#include "ray.h"
#include "sphere.h"
#include "colour.h"
#include "light.h"

void find_closest_intersection_point(ray *r, sphere **spheres, int num_spheres,
        vector3 **closest_intersection_point, vector3 **surface_normal, sphere **intersected_sphere) {    
    *closest_intersection_point = NULL;
    sphere *s;
    for (int i = 0; i < num_spheres; i++) {
        s = spheres[i];
        vector3 *sphere_intersection_point = intersect_sphere(r, s);
        if (sphere_intersection_point != NULL && distance(r->org, sphere_intersection_point) > SAME_SPHERE) {
            if (*closest_intersection_point == NULL || distance(r->org, *closest_intersection_point) < distance(r->org, sphere_intersection_point)) {
                *closest_intersection_point = sphere_intersection_point;
                if (intersected_sphere != NULL)
                    *intersected_sphere = s;
            }
            else
                free(sphere_intersection_point);
        }
    }

    if ((*closest_intersection_point) == NULL) 
        return;

    if (surface_normal != NULL) {
        *surface_normal = make_difference_vector(*closest_intersection_point, (*intersected_sphere)->pos);
        normalise(*surface_normal);
    }
    
}

colour *trace(ray *r, sphere **spheres, int num_spheres, light **lights, int num_lights, const int recursion_depth) {
    colour *c;

    vector3 *closest_intersection_point, *surface_normal;
    sphere *intersected_sphere;
    find_closest_intersection_point(r, spheres, num_spheres, &closest_intersection_point, &surface_normal, &intersected_sphere);
    
    
    if (closest_intersection_point == NULL)
    {
        c = make_colour(BG_COLOR_RED, BG_COLOR_GREEN, BG_COLOR_BLUE);
    }
     else {
        c = make_colour(0,0,0);

        light *l;
        for (int i = 0; i < num_lights; i++) {
            l = lights[i];

            vector3 *dir = make_difference_vector(l->pos, closest_intersection_point);
            normalise(dir);

            ray *shadow_ray = make_ray(closest_intersection_point, dir);
            vector3 *shadow_ray_intersection_point = NULL;

            sphere *s = NULL;
            find_closest_intersection_point(shadow_ray, spheres, num_spheres, &shadow_ray_intersection_point, NULL, &s);


            if (shadow_ray_intersection_point == NULL) {
                double dp = dot_product(dir, surface_normal);
                colour *clr = copy_colour(intersected_sphere->clr);
                mult(clr, max(dp, 0));
                add_colour(c, clr);
                free(clr);
            } else {
                
            }


            free_ray(shadow_ray);
        }
     }

    

    return c;
}

int main(int argc, char **argv) {
    sphere *spheres[] = {
        make_sphere(make_vect(-100, 20, 120), 110, make_colour(255, 0, 0)),
        make_sphere(make_vect(40, -40, 100), 90, make_colour(0, 255, 0))
    };

    light *lights[] = {
        make_light(make_vect(0,0,0))
       // make_light(make_vect(200, 200, 100))
    };

    int num_spheres = sizeof(spheres)/sizeof(spheres[0]);
    int num_lights = sizeof(lights)/sizeof(lights[0]);

    colour* image[WIDTH * HEIGHT];

    ray *r;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            r = make_ray(make_vect(0, 0, 0), make_normalised_vect(x-WIDTH/2, y-HEIGHT/2, SCREEN_DISTANCE));

            image[coords2index(x,y)] = trace(r, spheres, num_spheres, lights, num_lights, 0);

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

