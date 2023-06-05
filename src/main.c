#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "vect3.h"
#include "objs.h"

vect3 cast(double x, double y  ) {
    // constants
    vect3 origin = (vect3) {
        0,0,-1.0f
    };
    /* vect3 ray = (vect3){ */
    /*     x, y, 1.0f */
    /* }; */

    ray cast_ray = (ray){.origin = origin, .direction = (vect3){x,y,1.0f }};

    sphere sphere;
    sphere.pos = (vect3) {0,0,3};
    
    sphere.col = (vect3) {0,0,255};
    sphere.r = 0.1f;

    light global_light = {.pos = (vect3){-2,-2,-3}};

    /* double a = dot(ray, ray); */
    /* double b = 2.0f * dot(origin, ray); // going to be 0 */
    /* double c = dot(origin, origin) - sphere.r * sphere.r; */ 
    /* double d = (b*b) - (4.0f * a*c); */
    hit ray_hit = render_sphere(cast_ray, sphere, global_light);
    if (ray_hit.contact){
        return ray_hit.color;

    } else {
        return (vect3) { 0,100,0 };
    }

}

int main(int argc, char* argv[]) {
    int height = atoi(argv[1]);
    int width = atoi(argv[2]);

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

            vect3 col = cast(norm_x,norm_y);
            
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
