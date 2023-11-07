#include <omp.h>
#include <iostream>

int main() {

	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int min = 2147483647;
	int max = 0;

	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section 
		{
			for (int i = 0; i < 10; i++) {
				if (min > a[i]) {
                    min = a[i];
                }
			}
		}

		#pragma omp section
		{
			for (int i = 0; i < 10; i++) {
				if (max < b[i]) {
                    max = b[i];
                }
			}
		}
	}

	std::cout << "min: " << min << ", max: " << max << std::endl;

}