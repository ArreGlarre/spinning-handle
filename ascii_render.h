/*
This file contains the necessary functions and structures
to render a 3d object to the terminal using ascii characters.


*/

// INCLUDE STATEMENTS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
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

// CONSTANTS
char GRADIENT[10] = ".,:;!*#$@"; // 9 characters + \0
