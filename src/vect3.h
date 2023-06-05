#pragma once
typedef struct {
    double x,y,z;
} vect3;

double dot(vect3 first, vect3 second);
vect3 normalize(vect3 vect);

vect3 vect_add(vect3 first, vect3 second);
vect3 vect_sub(vect3 first, vect3 second);
vect3 vect_scalar_mult(vect3 vec, double s);
