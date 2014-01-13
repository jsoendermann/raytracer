#ifndef VECTOR3_H
#define VECTOR3_H

#define square(x) ((x)*(x))


typedef struct vector3 {
    double x;
    double y;
    double z;
} vector3;

vector3 *make_vect(double x, double y, double z);
vector3 *make_normalised_vect(double x, double y, double z);
vector3 *copy_vector(vector3 *v);

vector3 *make_difference_vector(vector3 *v1, vector3 *v2);

void normalise(vector3 *v);

void scale(vector3 *v, double s);
void shift(vector3 *v1, const vector3 *v2);
void invert(vector3 *v);
void mix_vectors(vector3 *v1, const vector3 *v2, double t);


double vector_length(vector3 *v);
double distance(vector3 *v1, vector3 *v2);
double dot_product(vector3 *v1, vector3 *v2);

char *vector_to_string(vector3 *v);
void print_vector(vector3 *v);

#endif
