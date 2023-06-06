#pragma once
typedef struct {
    float x,y,z;
} vect3;

float dot(vect3 first, vect3 second);
float dot_pow2(vect3 vect);
vect3 normalize(vect3 vect);

vect3 vect_add(vect3 first, vect3 second);
vect3 vect_sub(vect3 first, vect3 second);vect3 vect_scalar_mult(vect3 vec, float s);

// other utility functions

// credit to Eugene Hong
// https://github.com/awidesky/MyPapers
float fsqrt(float f);
