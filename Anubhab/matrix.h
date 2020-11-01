#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

struct matrix {
    unsigned int rows;
    unsigned int cols;

    uint32_t* data;
};

// number of 32bit units per line
#define matrix_pitch(cols) (cols / 32 + (cols % 32 ? 1 : 0))
#define matrix_get(m, r, c) ((m->data[pitch * r + c / 32] >> (c % 32)) & 1)

struct matrix* matrix_new(unsigned int rows, unsigned int cols) {
    struct matrix* mnew = (struct matrix*) malloc(sizeof(struct matrix));
    mnew->rows = rows;
    mnew->cols = cols;

    unsigned int pitch = matrix_pitch(cols);
    unsigned int total_size = sizeof(uint32_t) * pitch * rows;

    mnew->data = (uint32_t*) malloc(total_size);
    memset(mnew->data, 0, total_size);

    return mnew;
}

struct matrix* matrix_new_from_array(unsigned int rows, unsigned int cols, int* arr) {
    struct matrix* m = matrix_new(rows, cols);
    unsigned int pitch = matrix_pitch(cols);
    
    for (unsigned int r = 0; r < rows; r++) {
        uint32_t current_block = 0;
        uint32_t* block = &m->data[pitch * r];

        unsigned int c;
        for (c = 0; c < cols; c++) {
            current_block |= arr[r * cols + c] << (c % 32);

            if ((c & 31) == 31) { // this block is full
                *(block++) = current_block;
                current_block = 0;
            }
        }
        if ((c & 31) != 31) { // the block was not full
            *block = current_block; // write last block
        }
    }
    
    return m;
}

/*
struct matrix matrix_new_from_str(unsigned int rows, unsigned int cols, char* arr) {
    struct matrix m = matrix_new(rows, cols);
    unsigned int pitch = matrix_pitch(cols);
    unsigned int i = 0;

    for (unsigned int r = 0; r < rows; r++) {
        uint32_t current_block = 0;
        uint32_t* block = &m.data[pitch * r];

        for (unsigned int c = 0; c < cols; c++) {
            current_block |= (arr[i++]-'0') << (c % 32);

            if ((c & 31) == 31) { // this block is full
                *(block++) = current_block;
            }
        }
    }
    
    return m;
}
*/

struct matrix* matrix_copy(struct matrix* m) {
    struct matrix* mnew = matrix_new(m->rows, m->cols);
    
    unsigned int pitch = matrix_pitch(m->cols);    
    memcpy(mnew->data, m->data, sizeof(uint32_t) * pitch * m->rows);
    
    return mnew;
}

char* matrix_to_str(struct matrix* m) {
    unsigned int i = 0;
    unsigned int pitch = matrix_pitch(m->cols);

    char* str = (char*) malloc(m->rows * (m->cols + 1) + 1);

    for (int r = 0; r < m->rows; r++) {
        uint32_t* block = &m->data[pitch * r];
        uint32_t current_block = *(block++);

        for (int c = 0; c < m->cols; c++) {
            str[i++] = '0' + (current_block & 1);
            current_block = current_block >> 1;

            if ((c & 31) == 31) {
                current_block = *(block++);
            }
        }
        str[i++] = '\n';
    }

    str[i] = '\0';

    return str;
}

void matrix_swap_rows(struct matrix* m, unsigned int r1, unsigned int r2) {
    unsigned int pitch = matrix_pitch(m->cols);
    
    uint32_t* temp = (uint32_t*) malloc(pitch);

    memcpy(temp, &m->data[pitch * r1], pitch * sizeof(uint32_t));
    memcpy(&m->data[pitch * r1], &m->data[pitch * r2], pitch * sizeof(uint32_t));
    memcpy(&m->data[pitch * r2], temp, pitch * sizeof(uint32_t));

    free(temp);
}

void matrix_xor_rows(struct matrix* m, unsigned int r1, unsigned int r2) {
    unsigned int pitch = matrix_pitch(m->cols);

    for (int i = 0; i < pitch; ++i) {
        m->data[pitch * r1 + i] = m->data[pitch * r1 + i] ^ m->data[pitch * r2 + i];
    }
}

void matrix_rref(struct matrix* m) {
    unsigned int pitch = matrix_pitch(m->cols);
    unsigned int cols_done = 0;

    for (int r = 0; r < m->rows; ++r) {
        if (cols_done >= m->cols) break;

        unsigned int i = r;
        while (matrix_get(m, i, cols_done) == 0) {
            i++;
            if (i == m->rows) { // no 1s in this column
                if(++cols_done == m->cols) {
                    return;
                }

                i = r; // back to top
            }
        }

        if (i != r) { // row with 1 is not at the top most position
            matrix_swap_rows(m, i, r);
        }

        // remove 1s from higher rows
        for (unsigned int i = 0; i < r; ++i) {
            if (matrix_get(m, i, cols_done)) {
                matrix_xor_rows(m, i, r);
            }
        }

        // remove 1s from lower rows
        for (unsigned int i = r + 1; i < m->rows; ++i) {
            if (matrix_get(m, i, cols_done)) {
                matrix_xor_rows(m, i, r);
            }
        }

        cols_done++;
    }
}

#endif // MATRIX_H
