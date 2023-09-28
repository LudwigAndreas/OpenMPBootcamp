#include <iostream>
#include <omp.h>

int main()
{
    int a[12], b[12], c[12];

    // Первая параллельная область
    #pragma omp parallel num_threads(3)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        #pragma omp critical
        std::cout << "First section: num of threads = " << num_threads
                  << ", number = " << thread_num << std::endl;

        #pragma omp for schedule(static, 4)
        for (int i = 0; i < 12; i++)
        {
            a[i] = i + 1;
            b[i] = i + 2;
            #pragma omp critical
            std::cout << "a[" << i << "] = " << a[i] << ", "
                      << "b[" << i << "] = " << b[i] << std::endl;
        }
    }

    // Вторая параллельная область
    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        #pragma omp critical
        std::cout << "Second section: num of threads = " << num_threads
                  << ", number = " << thread_num << std::endl;

        #pragma omp for schedule(dynamic, 4)
        for (int i = 0; i < 12; i++)
        {
            c[i] = a[i] + b[i];
            #pragma omp critical
            std::cout << "c[" << i << "] = " << c[i] << std::endl;
        }
    }

    return 0;
}