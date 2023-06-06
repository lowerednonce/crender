#include <math.h>
#include <stdbool.h>

#include "objs.h"
#include "vect3.h"

hit render_sphere(ray render_ray, sphere sphere, light show_light) {
    hit result;
    vect3 oc = vect_sub(render_ray.origin, sphere.pos);

    double a = dot(render_ray.direction, render_ray.direction);
    double b = 2.0f * dot(render_ray.direction, oc);
    double c = dot_pow2(oc) - sphere.r * sphere.r; 
    double d = (b*b) - (4*a*c);

    if (d >= 0.0f) {
        result.contact = true;
        float t = ( - b - sqrt(d)) / ( 2 * a ); // cuadratic formula, saves a few calculations by doing it full here
        result.depth = t;

        vect3 n = normalize(vect_add(render_ray.origin, vect_scalar_mult(render_ray.direction, t)));
        float l = dot(n, normalize(show_light.pos));
        if (l < 0) {
            result.color = (vect3){0,0,0};
        } else {
            result.color = (vect3)vect_scalar_mult(sphere.col, l);
        }
        /* result.color = vect_scalar_mult(n, 255); */
    } else {
        result.contact = false;
    }

    return result;
}
