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
    vect3 center;
    vect3 normal;
    vect3 base_color;
} plane;

typedef struct {
    vect3 pos;
} light;

typedef struct {
    vect3 color;
    float depth;
    bool contact;
} hit;

typedef struct {
    sphere *spheres;
    size_t spheres_size;
    plane *planes;
    size_t planes_size;
} Scene;

hit render_sphere(ray ray, sphere sph, light shown_light);
hit render_plane(ray ray, plane pln, light shown_light);
