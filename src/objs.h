#include <stddef.h>
#include "vect3.h"

typedef struct {
    vect3 pos;
    vect3 col;
    float r;
} sphere;

typedef struct {
    vect3 origin;
    /* double fov; */
    vect3 direction;
} ray;

typedef struct {
    vect3 pos;
    vect3 size;
} plane;

typedef struct {
    vect3 pos;
} light;

typedef struct {
    vect3 color;
    double depth;
    bool contact;
} hit;

typedef struct {
    sphere *spheres;
    size_t spheres_size;
} Scene;

hit render_sphere(ray ray, sphere sphere, light shown_light);
