#include "oldpolynomial.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    //int arr[] = {1,1,0,1,1,1,0,1};
    char* str = "11011101";

    struct polynomial* p1 = polynomial_new_from_str("111");
    struct polynomial* p2 = polynomial_new_from_str("111");

    struct polynomial* q  = polynomial_new(30);
    struct polynomial* r  = polynomial_new(0);
    //polynomial_divide(p1, p2, q, r);

    polynomial_multiply(q, p1, p2);

    str = polynomial_to_str(p1);
    printf("%s\n", str);
    free(str);
    str = polynomial_to_str(p2);
    printf("%s\n", str);
    free(str);
    str = polynomial_to_str(q);
    printf("%s\n", str);
    free(str);
    str = polynomial_to_str(r);
    printf("%s\n", str);
    free(str);

    //str = polynomial_to_str(p2);
    //printf("%s\n", str);
    //free(str);

    free(p1);
    free(p2);
    
    return 0;
}
