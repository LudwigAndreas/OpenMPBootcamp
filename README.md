
# OpenMP Bootcamp

The OpenMP Bootcamp is an educational initiative aimed at providing individuals with a hands-on introduction to OpenMP, a widely-used API for parallel programming. In today's computing landscape, where multi-core processors are the norm, understanding how to harness the power of parallelism is crucial for optimizing application performance.

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
    2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
    3.1. [Part 1](#part-1-introduction-to-openmp) \
    3.2. [Part 2](#part-2-openmp-interation) \
    3.3. [Part 3](#part-3-synchronization)


## Chapter I

![Parallel Bootcamp](misc/images/abstract_lines.jpeg)

### Introduction

Welcome to the OpenMP Bootcamp! This bootcamp is designed to provide you with a comprehensive introduction to OpenMP, a powerful API for parallel programming. OpenMP allows you to harness the power of multi-core processors and parallel computing to improve the performance of your applications.

In this bootcamp, you will explore various aspects of OpenMP, including parallelization techniques, synchronization mechanisms, and practical examples. By the end of this bootcamp, you should have a solid understanding of how to parallelize your code and make it more efficient.

## Chapter II

### Information

OpenMP (Open Multi-Processing) is an API that supports multi-platform shared-memory multiprocessing programming in C, C++, and Fortran. It provides a set of compiler directives, library routines, and environment variables that enable developers to create parallel programs for a wide range of applications. OpenMP is particularly useful for taking advantage of multi-core processors and improving the performance of computationally intensive tasks.

## Chapter III

### Part 1. Introduction to OpenMP

Shared and protected variables. Access restrictions to variables, non-iterative work-sharing constructs. (10 points)

#### Task 1

Write a program where each thread prints its identifier, the total number of threads, and the string "Hello World." Run the program with 8 threads. Is the output always identical? Why? (1 point)

#### Task 2

Write a program in which you define two parallel regions. The execution of these regions depends on a conditional statement: #pragma omp parallel if (...). If the specified number of threads is greater than 2, the region is executed in parallel; otherwise, it is not. Set the number of threads before the first region to 3 and before the second region to 2. Inside these parallel regions, determine the number of threads and the thread number, and output the results to the screen. Verify the correctness of the program. (2 points)

#### Task 3

Write a program in which you declare and assign initial values to integer variables a and b. Define two parallel regions: the first with 2 threads and the second with 4 threads. In the first region, declare variables a and b as protected, with private and firstprivate access modes, respectively. Inside the region, determine the thread number and increment the values of these variables by that amount. Output the values of the variables before entering the parallel region, inside the parallel region, and after exiting the parallel region. For the second region, declare variable a as shared and variable b as protected with private access mode. Determine the thread number and decrement the values of these variables by that amount. Output the values of the variables before entering the parallel region, inside the parallel region, and after exiting the parallel region. Initialize uninitialized variables. (2 points)

#### Task 4

Write a program in which you declare and assign initial values to integer arrays a[10] and b[10]. Define a parallel region with a thread count of 2 and allocate code for the main thread (number 0) and the thread with number 1. The main thread (master) should find the minimum value of elements in array a, and the thread with number 1 should find the maximum value of elements in array b. Output the results to the screen. (2 points)

#### Task 5

Write a program in which you declare and assign initial values to elements of a two-dimensional array d[6][8]. Use a random number generator for initialization. Using the sections...section directive, define three sections for the following operations: the first section calculates the average value of elements in the two-dimensional array, the second section calculates the minimum and maximum values of elements in the two-dimensional array, and the third section calculates the count of elements in the array whose values are multiples of 3. In each section, determine and output the executing thread number and the results of the calculations. (3 points)

### Part 2. OpenMP Interation

Work-sharing constructs of iterative type. (11 points)

#### Task 6

Write a program in which you declare and assign initial values to an integer array a[100]. Use the parallel for construct and the reduction clause to calculate the arithmetic averages of the elements in array a. Calculate it once with reduction and once without. Compare the obtained values and explain any differences in the results. (2 points)

#### Task 7

Write a program in which you define two parallel regions, each containing a for loop for initializing elements of one-dimensional integer arrays a[12], b[12], and c[12]. Set the number of threads to 3 before the first region and to 4 before the second region. In the first parallel region, initialize elements of arrays a and b using static distribution of iterations. Choose the iteration chunk size yourself. In the second parallel region, initialize elements of array c according to the rule: c[i] = a[i] + b[i], using dynamic distribution of iterations. Choose the iteration chunk size yourself. In each region, determine and output the number of threads, the thread number, and the results of the loops. Verify the correctness of the program. (2 points)

#### Task 8

Write a program in which you declare an array of 16,000 elements and initialize it in such a way that the value of each array element is equal to its index. Then create a resulting array in which (except for the extreme elements), each element is the average of its neighboring elements: b[i] = (a[i-1] + a[i] + a[i+1])/3.0. Run the program with 8 processes using different types of work distribution (static, dynamic, guided, auto(runtime) if auto doesn't work) and observe the time for different chunk sizes. (4 points)

#### Task 9

Using the capabilities of OpenMP, write a program for matrix-vector multiplication. Compare the execution time of sequential and parallel programs (select the best schedule). Determine the matrix sizes at which the parallel program starts to outperform the sequential one. (3 points)

### Part 3. Synchronization

Synchronization operations (11 points)

#### Task 10

Write a program in which you declare and assign initial values to elements of a two-dimensional array d[6][8]. Use the omp parallel for directive and omp critical to determine the minimum and maximum values of elements in the two-dimensional array. Implement a reduction-like mechanism for max and min. Set the number of threads yourself. Output the results to the screen. (2 points)

#### Task 11

Write a program in which you declare and assign initial values to an array of integers a[30]. Use a random number generator for initialization. Use omp parallel for and omp atomic to calculate the count of array elements whose values are multiples of 9. Set the number of threads yourself. Output the results to the screen. (2 points)

#### Task 12

Write a program in which you declare and fill an array of integers with random values. Use OpenMP features to find the maximum value of elements that are multiples of 7. Determine the array length and the number of threads yourself. Output the results to the screen. Use omp_lock to synchronize numeric maximum values. (2 points)

#### Task 13

Modify Task 1 so that threads print their identifiers in reverse (decreasing) order. There are at least 5 ways to solve this. Try to find as many as possible. (1 point for each variant, maximum 5 points)
