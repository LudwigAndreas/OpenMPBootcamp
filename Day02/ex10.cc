#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

int main() {

    int height = 6;
    int width = 8;
	int d[height][width];
	int sum = 0;
	double mean = 0;
	int max = 0;
	int min = 2147483647;
	std::cout << "Array: " << std::endl;
	for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            d[i][j] = std::rand() / ((RAND_MAX + 1u) / 100);
			std::cout << d[i][j] << " ";
        }
		std::cout << std::endl;
    }
    size_t i = 0;
    size_t j = 0;
	#pragma omp parallel for private(i) private(j) shared(max,min)
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (max < d[i][j]) {
                #pragma omp critical
                if (max < d[i][j]) 
                    max = d[i][j]; 
            }
            if (min > d[i][j]) {
                #pragma omp critical
                if (min > d[i][j]) 
                    min = d[i][j];
            }
        }
    }

    std::cout << "Min: " << min << " Max: " << max << std::endl;
}
