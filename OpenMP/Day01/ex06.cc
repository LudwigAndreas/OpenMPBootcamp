#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {

	int a[100];
	int sum = 0;
    double mean;
	std::cout << "Array: " << std::endl;
	for (size_t i = 0; i < 100; ++i) {
        a[i] = std::rand() / ((RAND_MAX + 1u) / 100);
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    
    #pragma parallel for 
    for (size_t i = 0; i < 100; i++)
    {
        sum += a[i];
    }
    std::cout << "Parallel for mean: " << sum / 100 << std::endl;
    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (size_t i = 0; i < 100; i++)
    {
        sum += a[i];
    }
    std::cout << "Reduction mean: " << sum / 100 << std::endl;
    
    
	
}