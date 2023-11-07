#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

int main() {

    int len = 30;
	int a[len];
	int count = 0;

	std::cout << "Array: " << std::endl;
	for (size_t i = 0; i < len; ++i) {
        a[i] = std::rand() / ((RAND_MAX + 1u) / 100);
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

	#pragma omp parallel for
    for (size_t i = 0; i < len; i++) {
        if (a[i] % 9 == 0) { 
            #pragma omp atomic
            count++;
        }
    }
    std::cout << "Count: " << count << std::endl;
}
