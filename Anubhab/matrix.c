#include "matrix.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int arr[3][36] = {
        {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
        {1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}
    };
    
    char* str;

    struct matrix* m1 = matrix_new_from_array(3, 36, (int*)arr);
    struct matrix* m2 = matrix_copy(m1);

    matrix_xor_rows(m2, 0, 2);
    matrix_rref(m1);
    matrix_rref(m2);

    str = matrix_to_str(m1);
    printf("%s\n", str);
    free(str);

    str = matrix_to_str(m2);
    printf("%s\n", str);
    free(str);

    free(m1);
    free(m2);
    
    return 0;
}
