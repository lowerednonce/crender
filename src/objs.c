#include <math.h>
#include <stdbool.h>

#include "objs.h"
#include "vect3.h"

hit render_sphere(ray render_ray, sphere sphere, light show_light) {
    hit result;
    vect3 oc = vect_sub(render_ray.origin, sphere.pos);

    float a = dot(render_ray.direction, render_ray.direction);
    float b = 2.0f * dot(render_ray.direction, oc);
    float c = dot_pow2(oc) - sphere.r * sphere.r; 
    float d = (b*b) - (4*a*c);

    if (d >= 0.0f) {
        result.contact = true;
        float t = ( - b - fsqrt(d)) / ( 2 * a ); // quadratic formula, saves a few calculations by doing it full here
        result.depth = t;

        vect3 n = normalize(vect_add(render_ray.origin, vect_scalar_mult(render_ray.direction, t)));
        float l = dot(n, normalize(show_light.pos));
        if (l < 0) {
            result.color = (vect3){0,0,0};
        } else {
            result.color = (vect3)vect_scalar_mult(sphere.col, l);
        }
    } else {
        result.contact = false;
    }

    return result;
}

hit render_plane(ray ray, plane pln, light shown_light) {
    hit result;

   float d = dot(vect_sub(pln.center, ray.origin), pln.normal) / dot(ray.direction, pln.normal);
   if (d >= 0) {
       result.contact = true;
       result.depth = d;
       
       // always lit planes
       /* double l = dot(pln.normal, normalize(shown_light.pos)); */
        /* if (l < 0) { */
        /*     result.color = (vect3){0,0,0}; */
        /* } else { */
        /*     result.color = (vect3)vect_scalar_mult(pln.base_color, l); */
        /* } */
        result.color = pln.base_color;
   } else {
       result.contact = false;
   }

   return result;
}
