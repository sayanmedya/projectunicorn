#include "matrix.hpp"
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int main(int argc, char const *argv[]) {
    
    /*
    int arr[5][6] = {
        {0,1,1,0,0,1},
        {1,0,1,0,1,0},
        {0,1,0,1,0,1},
        {1,1,1,0,0,1},
        {1,1,0,1,1,0}
    };
    Matrix<5,6> m(arr);
    m.rref();
    cout << m << endl;
    */
    
    
    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_int_distribution<int> uniform_binary_dist(0,1);

    auto am = new Matrix<8,16>[1024];

    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 16; ++k) {
                am[i][j][k] = uniform_binary_dist(engine);
            }
        }
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 1024; ++i) {
        am[i].rref();
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Time: " << elapsed_seconds.count() << " s" << endl;
    
    cout << am[0];
    

    return 0;
}
