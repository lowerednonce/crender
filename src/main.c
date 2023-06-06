#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "vect3.h"
#include "objs.h"

vect3 cast(double x, double y, Scene scene) {
    // constants
    vect3 origin = (vect3) {
        0,0,-1.0f
    };
    /* vect3 ray = (vect3){ */
    /*     x, y, 1.0f */
    /* }; */
    float mindepth = 0;
    vect3 pixel_color = (vect3) {0,100,0}; // default background color

    ray cast_ray = (ray){.origin = origin, .direction = (vect3){x,y,1.0f }};
    light global_light = {.pos = (vect3){+3,-3,3}}; // coords different because the light's direction will get normalized

    hit ray_hit;
    for (int i = 0; i<scene.spheres_size; ++i) {
        ray_hit = render_sphere(cast_ray, scene.spheres[i], global_light);
        if(ray_hit.contact && (ray_hit.depth < mindepth || !mindepth)) {
            pixel_color = ray_hit.color;
            mindepth = ray_hit.depth;
        }
    }

    return pixel_color;
}

Scene make_scene() {
    Scene custom;

    sphere sphere1;
    sphere1.pos = (vect3) {-0.5f,0,3};
    sphere1.col = (vect3) {0,0,255};
    sphere1.r = 1.5f;

    sphere sphere2;
    sphere2.pos = (vect3) {+0.5f,0,2.5f};
    sphere2.col = (vect3) {255,0,0};
    sphere2.r = 1.0f;

    plane pln1;
    pln1.center = (vect3) {0,-3,0};
    pln1.normal = (vect3) {0,1,0};
    pln1.base_color = (vect3) {255,255,0};

    custom.spheres = (sphere*)malloc(2*sizeof(sphere)); 
    custom.spheres_size = 2;

    custom.planes = (plane*)malloc(1*sizeof(plane));
    custom.planes_size = 1;

    custom.spheres[0] = sphere1;
    custom.spheres[1] = sphere2;
    custom.planes[0]  = pln1;

    return custom;
}

int main(int argc, char* argv[]) {
    const int height = atoi(argv[1]);
    const int width = atoi(argv[2]);

    Scene myScene = make_scene();

    FILE *fp = fopen("render.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", height, width);

    double norm_x;
    double norm_y;

    clock_t start, end;
    start = clock();
    for(unsigned int y = 0; y<height; ++y) {
        norm_y = 2 * (((double)y) / height ) - 1.0f; 
        for (unsigned int x = 0; x<width; ++x) {
            static unsigned char color[3];
            norm_x = 2 * (((double)x) / width)   - 1.0f; 

            vect3 col = cast(norm_x,norm_y, myScene);
            
            color[0] = abs(col.x);
            color[1] = abs(col.y);
            color[2] = abs(col.z);
            /* R G B */
            fwrite(color, 1, 3, fp);
        }
    }
    end = clock();
    printf("Rendered scene in %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(fp);
    return 0;
}
