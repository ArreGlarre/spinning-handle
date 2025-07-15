/*
Testing the functions from linalg.h
*/

#include <stdio.h>
#include "linalg.h"

int test();

int main()
{
    test();
    return 0;
}

int test()
{
    // ALLT FUNGERAR  VERKAR DET SOM !!!!!
    float matrix[3][3];
    float pi = 3.14159;

    x_rotation(matrix, pi / 2);
    mat_display(matrix);
    putchar('\n');
    /*
    Expected:

    1 0 0
    0 0 -1
    0 1 0
    */

    y_rotation(matrix, pi / 2);
    mat_display(matrix);
    putchar('\n');
    /*
    expects:
    0 0 1
    0 1 0
    -1 0 0
    */

    z_rotation(matrix, pi / 2);
    mat_display(matrix);
    putchar('\n');
    /*
    expects:
    0 -1 0
    1 0 0
    0 0 1
    */

    float v[3] = {1, 2, 3};
    float u[3] = {-1, 4, 3};
    float w[3];
    int i;

    vectoradd(w, u, v);

    for (i = 0; i < 3; i++)
    {
        printf(" %.2lf", *(w + i));
    }
    putchar('\n');
    putchar('\n');

    float mat1[3][3] = {{2, 4, 1}, {0, 0, 1}, {2, 5, 1}};
    float mat2[3][3] = {{2, 4, 2}, {9, 0, 1}, {2, 0, 1}};

    matmulmat(matrix, mat1, mat2);

    mat_display(matrix);
    putchar('\n');

    matmulvec(v, matrix, w);

    for (i = 0; i < 3; i++)
    {
        printf(" %.2lf", *(v + i));
    }
    putchar('\n');

    DCM(matrix, pi / 2, pi / 2, 0);
    mat_display(matrix);

    putchar('\n');

    return 0;
}