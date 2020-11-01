#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct polynomial {
    unsigned int degree;
    uint32_t* data;
};

#define polynomial_pitch(degree) ((degree + 1) / 32 + ((degree + 1) % 32 ? 1 : 0))
#define polynomial_get(p,n) (((p->data[n >> 5]) >> (n & 31)) & 1)

struct polynomial* polynomial_new(unsigned int degree) {
    struct polynomial* pnew = (struct polynomial*) malloc(sizeof(struct polynomial));
    pnew->degree = degree;

    unsigned int pitch = polynomial_pitch(degree);
    pnew->data = (uint32_t*) malloc(pitch);
    memset(pnew->data, 0, pitch * sizeof(uint32_t));

    return pnew;
}

struct polynomial* polynomial_new_from_str(const char* str) {
    unsigned int degree = strlen(str) - 1;
    struct polynomial* p = polynomial_new(degree);
    
    uint32_t current_block = 0;
    int d;
    for (d = 0; d <= degree; d++) {
        current_block |= (str[degree - d] - '0') << (d % 32);

        if ((d & 31) == 31) { // this block is full
            p->data[d >> 5] = current_block;
            current_block = 0;
        }
    }
    if ((d & 31) != 31) { // the block was not full
        p->data[d >> 5] = current_block; // write last block
    }
    
    return p;
}

struct polynomial* polynomial_new_from_array(unsigned int degree, const int* arr) {
    struct polynomial* p = polynomial_new(degree);
    
    uint32_t current_block = 0;
    int d;
    for (d = 0; d <= degree; d++) {

        current_block |= arr[degree - d] << (d % 32);

        if ((d & 31) == 31) { // this block is full
            p->data[d >> 5] = current_block;
            current_block = 0;
        }
    }
    if ((d & 31) != 31) { // the block was not full
        p->data[d >> 5] = current_block; // write last block
    }
    
    return p;
}

struct polynomial* polynomial_copy(struct polynomial* p) {
    struct polynomial* pnew = polynomial_new(p->degree);
    
    unsigned int pitch = polynomial_pitch(p->degree);    
    memcpy(pnew->data, p->data, sizeof(uint32_t) * pitch);
    
    return pnew;
}

char* polynomial_to_str(struct polynomial* p) {
    unsigned int i = 0;
    unsigned int pitch = polynomial_pitch(p->degree);

    char* str = (char*) malloc(p->degree + 2);

    uint32_t current_block = p->data[p->degree >> 5];

    for (int d = p->degree; d >= 0; d--) {
        if ((d & 31) == 31) {
            current_block = p->data[d >> 5];
        }
        
        str[i++] = '0' + ((current_block >> (d % 32)) & 1);
    }
    str[i] = '\0';

    return str;
}

void polynomial_delete(struct polynomial* p) {
    free(p->data);
    p->degree = 0;
}

unsigned int polynomial_correct_degree(struct polynomial* p) {
    for (int d = p->degree; d >= 0; d--) {
        if (polynomial_get(p, d)) {
            printf("%u\n", d);
            //printf("%d %d %d %d\n", d, ((p->data[d >> 5]) >> (d & 32)) & 1, p->data[d >> 5], d & 31);
            p->degree = d;
            break;
        }
    }

    return p->degree;
}

void polynomial_xor(struct polynomial* result, struct polynomial* p1, struct polynomial* p2) {
    // assuming result->degree >= p1->degree >= p2->degree
    unsigned int pitch = polynomial_pitch(p2->degree);

    for (int i = 0; i < pitch; ++i) {
        result->data[i] = p1->data[i] ^ p2->data[i];
    }

    polynomial_correct_degree(result);
}

void polynomial_shift_left(struct polynomial* p, unsigned int n) {
    // assuming there is sufficient space and degree has been updated.
    while (n > 31) {
        polynomial_shift_left(p, 31);
        n -= 31;
    }
    unsigned int pitch = polynomial_pitch(p->degree);
    
    uint32_t last_block = 0;
    for (int i = 0; i < pitch; ++i) {
        uint32_t current_block = p->data[i];
        p->data[i] = (current_block << n) | (last_block >> (32 - n));
        last_block = current_block;
    }
}

void polynomial_multiply(struct polynomial* result, struct polynomial* p1, struct polynomial* p2) {
    unsigned int last_d = 0;
    struct polynomial* temp = polynomial_copy(p1);

    uint32_t current_block;
    for (int d = 0; d <= p2->degree; d++) {
        if ((d & 31) == 0) {
            current_block = p2->data[d >> 5];
        }

        if ((current_block >> (d % 32)) & 1) {
            polynomial_shift_left(temp, d - last_d);
            polynomial_xor(result, result, temp);
            last_d = d;
        }
    }

    polynomial_correct_degree(result);
}

void polynomial_divide(struct polynomial* dividend, struct polynomial* divisor, struct polynomial* quotient, struct polynomial* remainder) {
    int degree_diff = dividend->degree - divisor->degree;
    if (degree_diff < 0) {
        quotient = polynomial_new(0);
        remainder = polynomial_copy(dividend);
    }
}

#endif // POLYNOMIAL_H
