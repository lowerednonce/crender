#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct vect3 {
    double x,y,z;
};

struct sph {
    struct vect3 pos;
    struct vect3 col;
    float r;
};

double dot(struct vect3 first, struct vect3 second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

struct vect3 normalize(struct vect3 vect) {
    double len = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
    return (struct vect3) {
        vect.x / len,
        vect.y / len,
        vect.z / len,
    };
    
}

struct vect3 vect_add(struct vect3 first, struct vect3 second) {
    return (struct vect3) {
        first.x + second.x,
        first.y + second.y,
        first.z + second.z,
    };
}
struct vect3 vect_scalar_mult(struct vect3 vec, double s) {
    return (struct vect3) {
        vec.x * s,
        vec.y * s,
        vec.z * s,
    };
}

struct vect3 cast(double x, double y) {
    /* printf("casting ray at x: %f, y:%f\n", x, y); */
    // constants
    struct vect3 origin = (struct vect3) {
        0,0,-1.0f
    };
    struct vect3 ray = (struct vect3){
        x, y, 1.0f
    };
    struct sph sphere;
    sphere.pos = (struct vect3) {0,0,3};
    
    sphere.col = (struct vect3){255,0,0};
    sphere.r = 0.1f;

    struct vect3 light = (struct vect3) {-2,-2,-3};


    double a = dot(ray, ray);
    double b = 2.0f * dot(origin, ray); // going to be 0
    double c = dot(origin, origin) - sphere.r * sphere.r; 
    double d = (b*b) - (4.0f * a*c);


    if ( d >= 0.0f ) {
        float t = ( 0 - b - sqrt(d)) / (2.0f * a);
        struct vect3 n = normalize(vect_add(origin, vect_scalar_mult(ray, t)));
        /* printf("normal: %f, %f, %f\n", n.x, n.y, n.z); */
        float l = dot(n, normalize(light));
        if (l < 0 ) {
            return (struct vect3) {0,0,0};
        } else {
            return vect_scalar_mult(sphere.col, l);
        }

    } else {
        return (struct vect3) { 0,100,0 };
    }

}

int main(int argc, char* argv[]) {
    int height = atoi(argv[1]);
    int width = atoi(argv[2]);

    FILE *fp = fopen("render.ppm", "wb");

    fprintf(fp, "P6\n%d %d\n255\n", height, width);

    double norm_x;
    double norm_y;
    for(unsigned int y = 0; y<height; ++y) {
        for (unsigned int x = 0; x<width; ++x) {
            static unsigned char color[3];
            norm_y = (((double)y) / height ) - 0.5f; 
            norm_x = (((double)x) / width) - 0.5f; 
            // TODO: make ray from here
            //       see if it intersects with a sphere
            struct vect3 col = cast(norm_x,norm_y);
            /* col = vect_scalar_mult(col, 255); */
            
            color[0] = abs(col.x);
            color[1] = abs(col.y);
            color[2] = abs(col.z);
            /* R G B */
            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
    return 0;
}
