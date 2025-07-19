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
struct Surface *cylinder(float r, float L, int n, int N);

// MAIN
int main()
{
    // Declare variables
    int i;

    float r = 1;
    float L = 2;
    int n = 100;
    int N = 20;
    int N_tot = N * n;

    float roll = 0, pitch = 0, yaw = 0;
    float r_rate = 0.1, p_rate = 0.05, y_rate = 0.07;

    float center[3] = {3, -1, 0};

    // Allocate space
    struct Surface *cyl = cylinder(r, L, n, N);
    struct Surface *rotated_cyl;
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
        rotated_cyl = rotated_model(cyl, roll, pitch, yaw, N_tot, center);

        // draw
        draw(rotated_cyl, screen, N_tot);

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
    // Returns a pointer to a rectangle model. Will have N_tot = n*N

    int i, j, k;
    struct Surface *p_rectangle = (struct Surface *)malloc(n * N * sizeof(struct Surface));

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

struct Surface *cylinder(float r, float L, int n, int N)
{
    // Returns a pointer to a cylinder model.
    // cylinder has its axis along the x-axis and begins at x = 0.
    int i, j, k;
    struct Surface *p_cylinder = (struct Surface *)malloc(N * n * sizeof(struct Surface));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < n; j++)
        {
            k = i * n + j;
            p_cylinder[k].pos[0] = i * L / N;
            p_cylinder[k].pos[1] = r * cosf(2 * PI * j / n);
            p_cylinder[k].pos[2] = r * sinf(2 * PI * j / n);

            p_cylinder[k].n[0] = 0;
            p_cylinder[k].n[1] = cosf(2 * PI * j / n);
            p_cylinder[k].n[2] = sinf(2 * PI * j / n);
        }
    }

    return p_cylinder;
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