#include "matrix.h"

#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0f;
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = (i==j?1.0f:0.0f);
        }
    }
}

void init_scale_matrix(float matrix[3][3], float scale)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0f;
        }
    }
	matrix[0][0] = scale;
	matrix [1][1] = scale;
	matrix [2][2] = 1.0f;
}

void init_shift_matrix(float matrix[3][3], float dx, float dy)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 2; ++j) {
            matrix[i][j] = 0.0f;
        }
    }
	matrix[0][2] = dx;
	matrix[1][2] = dy;
	matrix[2][2] = 1.0f;
}

void init_rotate_matrix(float matrix[3][3], float deg)
{
	matrix[0][0] = (float)cos(deg);
	matrix[0][1] = (float)sin(deg)*-1.0f;
	matrix[0][2] = 0.0f;

    matrix[1][0] = (float)sin(deg);
    matrix[1][1] = (float)cos(deg);
    matrix[1][2] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 1.0f;
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
			c[i][j]= a[i][0]*b[0][j] + a[i][0]*b[0][j] + a[i][2]*b[2][j];
        }
    }
}

void transform_point(const float a[3][3], const float b[3], float c[3])
{
	int i;

    for (i = 0; i < 3; ++i) {
		c[i] = a[i][0]*b[0] + a[i][1]*b[1] + a[i][2]*b[2];
	}
}