#include <math.h>
#include "vect3.h"

float dot(vect3 first, vect3 second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

float dot_pow2(vect3 vect) {
    return dot(vect, vect);
}

vect3 normalize(vect3 vect) {
    float len = fsqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
    return (vect3) {
        vect.x / len,
        vect.y / len,
        vect.z / len,
    };
    
}

vect3 vect_add(vect3 first, vect3 second) {
    return (vect3) {
        first.x + second.x,
        first.y + second.y,
        first.z + second.z,
    };
}

vect3 vect_sub(vect3 first, vect3 second) {
    return (vect3) {
        first.x - second.x,
        first.y - second.y,
        first.z - second.z,
    };
}

vect3 vect_scalar_mult(vect3 vec, float s) {
    return (vect3) {
        vec.x * s,
        vec.y * s,
        vec.z * s,
    };
}

// utility functions

// credit to Eugene Hong
// https://github.com/awidesky/MyPapers
float fsqrt(float f) {
    int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);
}

