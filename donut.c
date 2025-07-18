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

/*PROTOTYPES*/
struct Surface *torus(float R, float r, int N, int n);

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
        rotated_donut = rotated_model(donut, roll, pitch, yaw, N_tot, center);

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
