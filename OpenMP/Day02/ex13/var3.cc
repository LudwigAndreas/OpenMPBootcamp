#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(8)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        
        #pragma omp for schedule(dynamic, 1)
        for (int i = num_threads - 1; i >= 0; i--) {
            #pragma omp critical
            {
                std::cout << "Thread " << i << " of " << num_threads << ": Hello World" << std::endl;
            }
        }
    }

    return 0;
}
