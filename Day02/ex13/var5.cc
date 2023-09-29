#include <iostream>
#include <omp.h>

 int main()
 {
    int num_threads = 8;
    int current = num_threads;

    #pragma omp parallel num_threads(num_threads)
    {
        int nthreads = omp_get_num_threads();
        std::cout << "Hello from thread "<< omp_get_thread_num() << ", nthreads " << omp_get_num_threads() << std::endl;
    }
}