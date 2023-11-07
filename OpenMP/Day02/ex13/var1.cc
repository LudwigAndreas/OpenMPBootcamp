#include <iostream>
#include <omp.h>

 int main()
 {
    #pragma omp parallel num_threads(8)
    {
        int nthreads = omp_get_num_threads();
        for (int i = nthreads - 1; i >= 0; i--)
        {
            #pragma omp barrier
            {
                if (i == omp_get_thread_num())
                {
                    #pragma omp critical
                    std::cout << "Hello from thread "<< omp_get_thread_num() << ", nthreads " << omp_get_num_threads() << std::endl;
                }
            }
        }
    }
}