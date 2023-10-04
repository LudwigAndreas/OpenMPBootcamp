#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {

	int d[6][8];
	int sum = 0;
	double mean = 0;
	int max = 0;
	int min = 2147483647;
	std::cout << "Array: " << std::endl;
	for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            d[i][j] = std::rand() / ((RAND_MAX + 1u) / 100);
			std::cout << d[i][j] << " ";
        }
		std::cout << std::endl;
    }

	#pragma omp parallel sections
	{
		#pragma omp section 
		{
			for (size_t i = 0; i < 6; i++) {
				for (size_t j = 0; j < 8; j++) {
					sum += d[i][j];
				}
			}
			mean = sum / (6 + 8);
			#pragma omp critical
			std::cout << "Mean " << omp_get_thread_num() << ": " << (int) mean << std::endl;
		}

		#pragma omp section
		{
			for (size_t i = 0; i < 6; i++) {
				for (size_t j = 0; j < 8; j++) {
					if (max < d[i][j]) {
						max = d[i][j];
					}
				}
			}
			#pragma omp critical
			std::cout << "Max " << omp_get_thread_num() << ": " << max << std::endl;
		}

		#pragma omp section
		{
			for (int i = 0; i < 6; i++) {
				for (size_t j = 0; j < 8; j++) {
					if (min > d[i][j]) {
						min = d[i][j];
					}
				}
			}
			#pragma omp critical
			std::cout << "Min " << omp_get_thread_num() << ": " << min << std::endl;
		}
	}
}