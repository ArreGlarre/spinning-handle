/*
This file contains a couple usefull functions for linear algebra.

* matmulmat function
* matmulvec function
* vector addition function
* rotation matrix functions
    {
        rotation around x
        rotation around y
        rotation around z

        full DCM
    }
* dot product
* cross product
* vector scalar product

*/

/*------------------------- INCLUDE STATEMENTS AND CONSTANTS ------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

/*----------------------------------- PROTOTYPES -----------------------------------------*/

void mat_display(float mat[3][3]);
void matmulmat(float result[3][3], float mat1[3][3], float mat2[3][3]);
void matmulvec(float result[3], float mat[3][3], float vector[3]);
void vectoradd(float result[3], float vector1[3], float vector2[3]);
float dot(float vector1[3], float vector2[3]);
void sprod(float result[3], float vector[3], float scalar);
void cprod(float result[3], float vector1[3], float vector2[3]);
void x_rotation(float result[3][3], float theta);
void y_rotation(float result[3][3], float theta);
void z_rotation(float result[3][3], float theta);

/*----------------------------------- FUNCTIONS ------------------------------------------*/
void mat_display(float mat[3][3])
{
    // Prints the matrix
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf(" %.2f", mat[i][j]);
        }
        putchar('\n');
    }
}

void matmulmat(float result[3][3], float mat1[3][3], float mat2[3][3])
{
    // computes the 3x3 matrix multiplication mat1 * mat2 and
    // stores the result in result.
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            result[i][j] = mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j] + mat1[i][2] * mat2[2][j];
        }
    }
}

void matmulvec(float result[3], float mat[3][3], float vector[3])
{
    // computes result = mat * vec
    int i;

    for (i = 0; i < 3; i++)
    {
        result[i] = vector[0] * mat[i][0] + vector[1] * mat[i][1] + vector[2] * mat[i][2];
    }
}

void vectoradd(float result[3], float vector1[3], float vector2[3])
{
    // computes the sum of 2 vectors and stores it in result
    int i;
    for (i = 0; i < 3; i++)
    {
        result[i] = vector1[i] + vector2[i];
    }
}

float dot(float vector1[3], float vector2[3])
{
    // returns the dot product of two 3D arrays
    int i;
    float sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += vector1[i] * vector2[i];
    }
    return sum;
}

void sprod(float result[3], float vector[3], float scalar)
{
    // computes scalar * vector
    int i;
    for (i = 0; i < 3; i++)
    {
        result[i] = vector[i] * scalar;
    }
}

void cprod(float result[3], float vector1[3], float vector2[3])
{
    // Computes the cross product vector1 x vector 2 and stores in result
}

void x_rotation(float result[3][3], float theta)
{
    // computes the rotation matrix around the x-axis with theta radians.
    result[0][0] = 1;
    result[0][1] = 0;
    result[0][2] = 0;

    result[1][0] = 0;
    result[1][1] = cosf(theta);
    result[1][2] = -sinf(theta);

    result[2][0] = 0;
    result[2][1] = sinf(theta);
    result[2][2] = cosf(theta);
}

void y_rotation(float result[3][3], float theta)
{
    // computes the rotation matrix around the y-axis with theta radians.
    result[0][0] = cosf(theta);
    result[0][1] = 0;
    result[0][2] = sinf(theta);

    result[1][0] = 0;
    result[1][1] = 1;
    result[1][2] = 0;

    result[2][0] = -sinf(theta);
    result[2][1] = 0;
    result[2][2] = cosf(theta);
}

void z_rotation(float result[3][3], float theta)
{
    // computes the rotation matrix around the z-axis with theta radians.
    result[0][0] = cosf(theta);
    result[0][1] = -sinf(theta);
    result[0][2] = 0;

    result[1][0] = sinf(theta);
    result[1][1] = cosf(theta);
    result[1][2] = 0;

    result[2][0] = 0;
    result[2][1] = 0;
    result[2][2] = 1;
}

void DCM(float result[3][3], float roll, float pitch, float yaw)
{
    // Turns result into a full on DCM with roll, pitch and yaw.
    // v_e = DCM v_b
    float x[3][3];
    float y[3][3];
    float z[3][3];
    float temp[3][3];

    x_rotation(x, roll);
    y_rotation(y, pitch);
    z_rotation(z, yaw);

    matmulmat(temp, y, x);
    matmulmat(result, z, temp);
}