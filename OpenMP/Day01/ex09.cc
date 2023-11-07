#include <iostream>
#include <chrono>
#include <omp.h>

void matrix_vector_multiply_parallel(int n, int m, double** matrix, double* vector, double* result) {
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < m; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void matrix_vector_multiply_sequential(int n, int m, double** matrix, double* vector, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < m; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int n = 10000;
    int m = 10000;

    double** matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (double)i + j;
        }
    }
    double* vector = new double[m];
    for (int i = 0; i < m; i++) {
        vector[i] = (double)i;
    }
    double* result = new double[n];

    auto start = std::chrono::high_resolution_clock::now();
    matrix_vector_multiply_sequential(n, m, matrix, vector, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto sequential_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Sequential execution time: " << sequential_duration << "ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    matrix_vector_multiply_parallel(n, m, matrix, vector, result);
    end = std::chrono::high_resolution_clock::now();
    auto parallel_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Parallel execution time: " << parallel_duration << "ms" << std::endl;

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vector;
    delete[] result;

    return 0;
}