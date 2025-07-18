/*
SPINNING ASCII DONUT

*/

/*INCLUDE STATEMENTS*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "ascii_render.h"

/*CONSTANTS*/
int RES = 50;

float LIGHT[3] = {0, -1, -1};

/*PROTOTYPES*/
struct Surface *torus(float R, float r, int N, int n);
struct Surface *rotated_object(struct Surface *torus, float roll, float pitch, float yaw, int N_tot, float center[3]);
void draw(struct Surface *torus, struct Pixel *screen, int N_tot);

/*MAIN*/
int main()
{
    float R = 2.5;
    float r = 1;
    int N = 200;
    int n = 100;
    float center[3] = {6, 0, 0};
    int N_tot = n * N;

    // allocate space for stuff
    struct Surface *donut = torus(R, r, N, n);
    struct Surface *rotated_donut;
    struct Pixel *screen = (struct Pixel *)malloc(RES * RES * sizeof(struct Pixel));

    // Motion parameters
    float pitch = 0, roll = 0, yaw = 0;
    float p_rate = 0.1, r_rate = 0.06, y_rate = 0.03;

    while (1)
    {
        // clear screen
        for (int i = 0; i < RES * RES; i++)
        {
            screen[i].shade = ' ';
            screen[i].distance = 100;
        }
        // rotate
        rotated_donut = rotated_object(donut, roll, pitch, yaw, N_tot, center);

        // draw
        draw(rotated_donut, screen, N_tot);

        // update euler angles
        pitch += p_rate;
        roll += r_rate;
        yaw += y_rate;

        // wait a lil
        usleep(150 * 1000);
    }
    putchar('\n');
}

/*FUNCTIONS*/

struct Surface *torus(float R, float r, int N, int n)
{
    // returns a pointer to a bunch of Surfaces that make a torus.
    int i, j, k;
    float theta;
    float phi;

    struct Surface *p_torus = (struct Surface *)malloc(n * N * sizeof(struct Surface));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < n; j++)
        {
            k = n * i + j;
            phi = 2 * PI / N * i;
            theta = 2 * PI / n * j;

            p_torus[k].pos[0] = (R + r * cosf(theta)) * cosf(phi);
            p_torus[k].pos[1] = (R + r * cosf(theta)) * sinf(phi);
            p_torus[k].pos[2] = r * sin(theta);

            p_torus[k].n[0] = cosf(theta) * cosf(phi);
            p_torus[k].n[1] = cosf(theta) * sinf(phi);
            p_torus[k].n[2] = sinf(theta);
        }
    }

    return p_torus;
}

struct Surface *rotated_object(struct Surface *torus, float roll, float pitch, float yaw, int N_tot, float center[3])
{
    // Returns a pointer to an identical torus, just rotated (and also add the center vector)
    struct Surface *rotated_torus = (struct Surface *)malloc(N_tot * sizeof(struct Surface));
    float matrix[3][3];
    float temp[3];

    DCM(matrix, roll, pitch, yaw);

    for (int i = 0; i < N_tot; i++)
    {
        matmulvec(temp, matrix, torus[i].pos);
        vectoradd(rotated_torus[i].pos, temp, center);

        matmulvec(rotated_torus[i].n, matrix, torus[i].n);
    }

    return rotated_torus;
}

void draw(struct Surface *torus, struct Pixel *screen, int N_tot)
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

        y = torus[i].pos[1] / torus[i].pos[0];
        z = torus[i].pos[2] / torus[i].pos[0];

        inty = (int)rintf((y + 1) * RES / 2);
        intz = (int)rintf((z + 1) * RES / 2);

        if (inty >= 0 && inty < RES && intz >= 0 && intz < RES)
        {
            // set distance and shade
            if (dot(torus[i].pos, torus[i].pos) < screen[RES * intz + inty].distance)
            {
                screen[RES * intz + inty].distance = dot(torus[i].pos, torus[i].pos);

                shadef = dot(nlight, torus[i].n) * (float)5 + (float)5;
                shadei = (int)(shadef >= 8 ? 8 : shadef);
                screen[RES * intz + inty].shade = GRADIENT[shadei];
            }
        }
    }

    for (i = 0; i < RES * RES; i++)
    {
        if (i % RES == 0)
        {
            printf("\n");
        }
        putchar(screen[i].shade);
    }
}
