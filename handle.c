/*
Here is where the magic is gonna happen :)

*/
// INCLUDE STATEMENTS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "ascii_render.h"

// STRUCTS

// CONSTANTS

// PROTOTYPES
struct Surface *rectangle(float l, float L, int n, int N);

// MAIN
int main()
{
    // Declare variables
    int i;

    float l = 2;
    float L = 4;
    int n = 20;
    int N = 40;
    int N_tot = N * n;

    float roll = 0, pitch = 0, yaw = 0;
    float r_rate = 0.1, p_rate = 0.05, y_rate = 0;

    float center[3] = {5, -1, 0};

    // Allocate space
    struct Surface *rect = rectangle(l, L, n, N);
    struct Surface *rotated_rect;
    struct Pixel *screen = (struct Pixel *)malloc(ZRES * YRES * sizeof(struct Pixel));

    while (1)
    {
        // clear screen
        for (i = 0; i < ZRES * YRES; i++)
        {
            screen[i].distance = 100;
            screen[i].shade = ' ';
        }

        // rotate
        rotated_rect = rotated_model(rect, roll, pitch, yaw, N_tot, center);

        // draw
        draw(rotated_rect, screen, N_tot);

        // update euler angles
        roll += r_rate;
        pitch += p_rate;
        yaw += y_rate;

        // wait
        usleep(150 * 1000);
    }

    return 0;
}

// FUNCTIONS

struct Surface *rectangle(float l, float L, int n, int N)
{
    // Returns a pointer to a rectangle model.

    int i, j, k;
    float x, y, z;
    struct Surface *p_rectangle = (struct Surface *)malloc((2 * n * n + 4 * n * N) * sizeof(struct Surface));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < n; j++)
        {
            k = i * n + j;
            p_rectangle[k].pos[0] = L / N * i;
            p_rectangle[k].pos[1] = l / n * j;
            p_rectangle[k].pos[2] = 0;

            p_rectangle[k].n[0] = 0;
            p_rectangle[k].n[1] = 0;
            p_rectangle[k].n[2] = 1;
        }
    }
    return p_rectangle;
}

struct Surface *cylinder()
{
    // Returns a pointer to a cylinder model.
}

struct Surface *handle()
{
    // Returns a pointer to a Handle, made up of a cylinder and a cuboid
}

struct matrix *I_handle()
{
    // Returns the Inertia tensor of a handle with homogenous mass dist.
}

float *COM()
{
    // Calculates the center of mass of the handle.
}

float *f()
{
    // the time derivative of the state-vector, given, the state vector.
}

void RK4_integrate()
{
    // Integrate a timestep using RK4 integration
}

void f_euler_integrate()
{
    // integrate a timestep using forward euler.
}