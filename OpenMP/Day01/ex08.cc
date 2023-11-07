#include <iostream>
#include <cstdlib>
#include <chrono>
#include <omp.h>

const int ARRAY_SIZE = 16000;

void initializeArray(int* arr) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i;
    }
}

int main() {
    int* inputArray = new int[ARRAY_SIZE];
    int* resultArray = new int[ARRAY_SIZE];

    initializeArray(inputArray);

    int numThreads = 8;
    omp_set_num_threads(numThreads);

    std::cout << "Static scheduling:" << std::endl;
    for (int chunkSize = 1; chunkSize <= 1000; chunkSize *= 10) {
        std::cout << "\tChunk size: " << chunkSize << std::endl;
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for schedule(static, chunkSize)
        for (int i = 0; i < ARRAY_SIZE; i++) {
            resultArray[i] = inputArray[i];
        }
        
        #pragma omp parallel for schedule(static, chunkSize)
        for (int i = 1; i < ARRAY_SIZE - 1; i++) {
            resultArray[i] = (inputArray[i-1] + inputArray[i] + inputArray[i+1]) / 3.0;
        }
        resultArray[0] = inputArray[0];
        resultArray[ARRAY_SIZE - 1] = inputArray[ARRAY_SIZE - 1];
        
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << "\t\tTime Taken: " << duration << " microseconds" << std::endl;
    }

    std::cout << "Dynamic scheduling:" << std::endl;
    for (int chunkSize = 1; chunkSize <= 1000; chunkSize *= 10) {
        std::cout << "\tChunk size: " << chunkSize << std::endl;
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for schedule(dynamic, chunkSize)
        for (int i = 0; i < ARRAY_SIZE; i++) {
            resultArray[i] = inputArray[i];
        }
        
            #pragma omp parallel for schedule(dynamic, chunkSize)
        for (int i = 1; i < ARRAY_SIZE - 1; i++) {
            resultArray[i] = (inputArray[i-1] + inputArray[i] + inputArray[i+1]) / 3.0;
        }
        resultArray[0] = inputArray[0];
        resultArray[ARRAY_SIZE - 1] = inputArray[ARRAY_SIZE - 1];
        
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << "\t\tTime Taken: " << duration << " microseconds" << std::endl;
    }

    std::cout << "Guided scheduling:" << std::endl;
    for (int chunkSize = 1; chunkSize <= 1000; chunkSize *= 10) {
        std::cout << "\tChunk size: " << chunkSize << std::endl;
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for schedule(guided, chunkSize)
        for (int i = 0; i < ARRAY_SIZE; i++) {
            resultArray[i] = inputArray[i];
        }
        
        #pragma omp parallel for schedule(guided, chunkSize)
        for (int i = 1; i < ARRAY_SIZE - 1; i++) {
            resultArray[i] = (inputArray[i-1] + inputArray[i] + inputArray[i+1]) / 3.0;
        }
        resultArray[0] = inputArray[0];
        resultArray[ARRAY_SIZE - 1] = inputArray[ARRAY_SIZE - 1];
        
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << "\t\tTime Taken: " << duration << " microseconds" << std::endl;
    }

    std::cout << "Auto scheduling:" << std::endl;
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(auto)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        resultArray[i] = inputArray[i];
    }
    
    #pragma omp parallel for schedule(auto)
    for (int i = 1; i < ARRAY_SIZE - 1; i++) {
        resultArray[i] = (inputArray[i-1] + inputArray[i] + inputArray[i+1]) / 3.0;
    }
    resultArray[0] = inputArray[0];
    resultArray[ARRAY_SIZE - 1] = inputArray[ARRAY_SIZE - 1];
    
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "\t\tTime taken: " << duration << " microseconds" << std::endl;

    delete[] inputArray;
    delete[] resultArray;
}