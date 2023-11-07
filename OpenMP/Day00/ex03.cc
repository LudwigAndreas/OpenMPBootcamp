#include <omp.h>
#include <iostream>

int main() {

	int a = 0;
    int b = 0;

	std::cout << "#before_scope a: " << a << " b: " << b << std::endl;

	#pragma omp parallel num_threads(2) private(a) firstprivate(b)
	{
		a = 0;
		a += omp_get_thread_num();
		b += omp_get_thread_num();
		#pragma omp critical
        std::cout << "#in_scope " << omp_get_thread_num() << " a: " << a << " b: " << b << std::endl;
	}

	std::cout << "#after_scope a: " << a << " b: " << b << std::endl;

	#pragma omp parallel num_threads(4) shared(a) private(b)
	{
		b = 0;
		#pragma omp atomic
		a -= omp_get_thread_num();
		b -= omp_get_thread_num();
		#pragma omp critical
		std::cout << "#in_scope " << omp_get_thread_num() << " a: " << a << " b: " << b << std::endl;
	}
	std::cout << "#after_scope a: " << a << " b: " << b << std::endl;
}