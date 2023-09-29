#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(8)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        #pragma omp for ordered
        for (int i = 0; i < num_threads; i++) {
            #pragma omp ordered
            {
                int reversed_thread_id = num_threads - i - 1;
                std::cout << "Thread " << reversed_thread_id << " of " << num_threads << ": Hello World" << std::endl;
            }
        }
    }

    return 0;
}
