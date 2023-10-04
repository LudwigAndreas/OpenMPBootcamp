#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

int main() {

    int len = 100;
	int a[len];
	int max = 0;
    omp_lock_t lock;

	std::cout << "Array: " << std::endl;
	for (size_t i = 0; i < len; ++i) {
        a[i] = std::rand() / ((RAND_MAX + 1u) / 100);
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    omp_init_lock(&lock);
	#pragma omp parallel for
    for (size_t i = 0; i < len; i++) {
        if (a[i] % 7 == 0 && a[i] > max) { 
            omp_set_lock(&lock);
            if (a[i] > max) { 
                max = a[i];
                std::cout << "Thread: " << omp_get_thread_num() << " max = " << a[i] << std::endl;
            }
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
    std::cout << "Max: " << max << std::endl;
}
