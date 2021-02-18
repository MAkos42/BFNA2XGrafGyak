#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
* Initializes an identity matrix.
*/
void init_identity_matrix(float matrix[3][3]);

/**
* Initializes a scale matrix.
*/
void init_scale_matrix(float matrix[3][3], float scale);

/**
* Initializes a shift matrix.
*/
void init_shift_matrix(float matrix[3][3], float dx, float dy);

/**
* Initializes a rotate matrix.
*/
void init_rotate_matrix(float matrix[3][3], float deg);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Multiply matrices.
 */
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Apply matrix to transform a point.
 */
void transform_point(const float a[3][3], const float b[3], float c[3]);
#endif // MATRIX_H

