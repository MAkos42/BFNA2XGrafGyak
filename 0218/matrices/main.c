#include "matrix.h"

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

	init_identity_matrix(c);
	printf("Identity matrix:\n");
    print_matrix(c);

    init_scale_matrix(c, 1.34f);
    printf("Scale matrix:\n");
    print_matrix(c);

    init_shift_matrix(c, 4.0f, -2.0f);
    printf("Shift matrix:\n");
    print_matrix(c);

    init_rotate_matrix(c, 60.0f);
    printf("Rotate matrix:\n");
    print_matrix(c);
	return 0;
}

