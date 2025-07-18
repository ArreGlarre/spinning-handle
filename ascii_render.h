/*
This file contains the necessary functions and structures
to render a 3d object to the terminal using ascii characters.


*/

// INCLUDE STATEMENTS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"

// STRUCTS

struct Pixel
{
    char shade;
    float distance;
};

struct Surface
{
    float pos[3];
    float n[3];
};

// PROTOTYPES

struct Surface *rotated_model(struct Surface *model, float roll, float pitch, float yaw, int N_tot, float center[3]);
void draw(struct Surface *model, struct Pixel *screen, int N_tot);

// CONSTANTS
char GRADIENT[10] = ".,:;!*#$@"; // 9 characters + \0. Will not work otherwise.
float LIGHT[3] = {0, -1, -1};
int ZRES = 40;
int YRES = 80;

// FUNCTIONS

struct Surface *rotated_model(struct Surface *model, float roll, float pitch, float yaw, int N_tot, float center[3])
{
    // Returns a pointer to an identical model (pointer to a N_tot long array of surface objects i guess)
    //, just rotated (and also add the center vector)
    struct Surface *rotated_torus = (struct Surface *)malloc(N_tot * sizeof(struct Surface));
    float matrix[3][3];
    float temp[3];

    DCM(matrix, roll, pitch, yaw);

    for (int i = 0; i < N_tot; i++)
    {
        matmulvec(temp, matrix, model[i].pos);
        vectoradd(rotated_torus[i].pos, temp, center);

        matmulvec(rotated_torus[i].n, matrix, model[i].n);
    }

    return rotated_torus;
}

void draw(struct Surface *model, struct Pixel *screen, int N_tot)
{
    /*
    loop over all Surfaces:
    * project to screen coordinates.
    * check if its inside bounds.
    * check if it has been drawn there (closer or at all)
    * compute shade
    * set shade and new distance value
    */

    int i, inty, intz;
    float y, z;
    float shadef;
    int shadei;
    float nlight[3];
    float light_mag;

    light_mag = (float)sqrt(dot(LIGHT, LIGHT));

    sprod(nlight, LIGHT, (float)1 / light_mag);

    for (i = 0; i < N_tot; i++)
    {

        y = model[i].pos[1] / model[i].pos[0];
        z = model[i].pos[2] / model[i].pos[0];

        inty = (int)rintf((y + 1) * YRES / 2);
        intz = (int)rintf((z + 1) * ZRES / 2);

        if (inty >= 0 && inty < YRES && intz >= 0 && intz < ZRES)
        {
            // set distance and shade
            if (dot(model[i].pos, model[i].pos) < screen[YRES * intz + inty].distance)
            {
                screen[YRES * intz + inty].distance = dot(model[i].pos, model[i].pos);

                shadef = dot(nlight, model[i].n) * (float)5 + (float)5;
                shadei = (int)(shadef >= 8 ? 8 : shadef);
                screen[YRES * intz + inty].shade = GRADIENT[shadei];
            }
        }
    }

    for (i = 0; i < YRES * ZRES; i++)
    {
        if (i % YRES == 0)
        {
            printf("\n");
        }
        putchar(screen[i].shade);
    }
}
