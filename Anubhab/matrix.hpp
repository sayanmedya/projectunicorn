#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <string>
#include <bitset>
#include <iostream>

template <unsigned int R, unsigned int C> class Matrix {
public:
    Matrix() {}

    Matrix(int arr[R][C]) {
        for (unsigned r = 0; r < R; r++) {
            for (unsigned c = 0; c < C; c++) {
                data[r][c] = arr[r][c];
            }
        }
    }

    std::bitset<C>& operator[](int index) {
        return data[index];
    };

    friend std::ostream& operator<<(std::ostream& os, const Matrix<R, C>& m) {
        for (unsigned int r = 0; r < R; ++r) {
            for (unsigned c = 0; c < C; c++) {
                os << m.data[r][c];
            }
            os << std::endl;
            //os << std::endl << m.data[r];
        }

        return os;
    }

    void swapRows(unsigned int r1, unsigned int r2) {
        std::swap(data[r1], data[r2]);
    }

    void rref() {
        unsigned int cols_done = 0;

        for (int r = 0; r < R; ++r) {
            if (cols_done >= C) break;

            unsigned int i = r;
            while (data[i][cols_done] == 0) {
                i++;
                if (i == R) { // no 1s in this column
                    if(++cols_done == C) {
                        return;
                    }

                    i = r; // back to top
                }
            }

            if (i != r) { // row with 1 is not at the top most position
                swapRows(i,r);
            }

            // remove 1s from higher rows
            for (unsigned int i = 0; i < r; ++i) {
                if (data[i][cols_done]) {
                    data[i] ^= data[r];
                }
            }

            // remove 1s from lower rows
            for (unsigned int i = r + 1; i < R; ++i) {
                if (data[i][cols_done]) {
                    data[i] ^= data[r];
                }
            }

            cols_done++;
        }
    }
private:
    std::bitset<C> data[R];
};

#endif // MATRIX_HPP_INCLUDED
