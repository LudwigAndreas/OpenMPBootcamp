#include <iostream>
#include <omp.h>
#include <thread>

 int main()
 {
    #pragma omp parallel num_threads(8)
    {
        int nthreads = omp_get_num_threads();

        std::this_thread::sleep_for(std::chrono::milliseconds(1 * (omp_get_num_threads() - omp_get_thread_num())));
        std::cout << "Hello from thread "<< omp_get_thread_num() << ", nthreads " << omp_get_num_threads() << std::endl;
    }
}