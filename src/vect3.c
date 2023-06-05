#include <math.h>
#include "vect3.h"

double dot(vect3 first, vect3 second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

vect3 normalize(vect3 vect) {
    double len = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
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

vect3 vect_scalar_mult(vect3 vec, double s) {
    return (vect3) {
        vec.x * s,
        vec.y * s,
        vec.z * s,
    };
}

