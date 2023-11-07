#include <iostream>
#include <omp.h>

 int main()
 {
    int num_threads = 8;

    int current_thread = num_threads;
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel num_threads(num_threads)
    {
        int nthreads = omp_get_num_threads();
        while(current_thread != 0)
        {
            omp_set_lock(&lock);
            if (current_thread - 1 == omp_get_thread_num()) {
                #pragma omp critical
                std::cout << "Hello from thread "<< omp_get_thread_num() << ", nthreads " << omp_get_num_threads() << std::endl;
                current_thread--;
            }
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
}