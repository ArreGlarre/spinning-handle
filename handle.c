/*
Here is where the magic is gonna happen :)

*/
// INCLUDE STATEMENTS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ascii_render.h"

// STRUCTS

// CONSTANTS

// PROTOTYPES

// MAIN
int main()
{

    return 0;
}

// FUNCTIONS

struct Surface *cuboid()
{
    // Returns a pointer to a cuboid model.
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