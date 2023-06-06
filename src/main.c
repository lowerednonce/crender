#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "vect3.h"
#include "objs.h"

vect3 cast(double x, double y, int posz  ) {
    // constants
    vect3 origin = (vect3) {
        0,0,-1.0f
    };
    /* vect3 ray = (vect3){ */
    /*     x, y, 1.0f */
    /* }; */

    ray cast_ray = (ray){.origin = origin, .direction = (vect3){x,y,1.0f }};

    sphere sphere1;
    sphere1.pos = (vect3) {-0.5f,0,3};
    sphere1.col = (vect3) {0,0,255};
    sphere1.r = 1.5f;

    sphere sphere2;
    sphere2.pos = (vect3) {+0.5f,0,2.5f};
    sphere2.col = (vect3) {255,0,0};
    sphere2.r = 1.0f;

    light global_light = {.pos = (vect3){+2,-2,3}};

    hit ray_hit1 = render_sphere(cast_ray, sphere1, global_light);
    hit ray_hit2 = render_sphere(cast_ray, sphere2, global_light);
    
    /* if(ray_hit1.contact) { */
    /*     return ray_hit1.color; */
    /* } else { return (vect3) {0,100,0}; } */

    if (ray_hit1.contact && ray_hit2.contact){
        if (ray_hit1.depth <= ray_hit2.depth){
            return ray_hit1.color;
        } else {
            return ray_hit2.color;
        }
    } else if (ray_hit1.contact) { return ray_hit1.color; }
    else if (ray_hit2.contact) {return ray_hit2.color; }
    else {
        // background
        return (vect3) { 0,100,0 };
    }

}

int main(int argc, char* argv[]) {
    const int height = atoi(argv[1]);
    const int width = atoi(argv[2]);
    const int posz = atoi(argv[3]);

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

            vect3 col = cast(norm_x,norm_y, posz);
            
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
