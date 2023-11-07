
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

![Parallel Bootcamp](../misc/images/abstract_lines.jpeg)

### Introduction

Welcome to the MPI Bootcamp! This program is crafted to offer you a thorough introduction to MPI, a robust API for parallel programming. MPI empowers you to leverage the capabilities of multi-core processors and parallel computing to enhance your applications' performance.

Throughout this bootcamp, you'll delve into different facets of MPI, covering parallelization strategies, synchronization mechanisms, and hands-on examples. By the conclusion of this bootcamp, you should possess a strong grasp of parallelizing your code and optimizing its efficiency using MPI.

## Chapter II

### Information

Open MPI (Message Passing Interface) is an open-source framework designed for parallel and distributed computing. It enables the development of high-performance, scalable applications by allowing multiple processes to communicate and collaborate in a coordinated manner. Here are some basic terms associated with Open MPI:

MPI Process (Rank): In the context of MPI, a process is an instance of a program that is capable of executing independently. Each process is assigned a unique identifier called a rank, which distinguishes it from other processes.

Communicator: A communicator is a group of MPI processes that can communicate with each other. It defines the scope of communication and is identified by a communicator handle.

Point-to-Point Communication: This involves communication between two specific MPI processes. The fundamental operations for point-to-point communication are MPI_Send (sending data) and MPI_Recv (receiving data).

Collective Communication: Collective communication involves communication among a group of processes. Common operations include broadcast (MPI_Bcast), scatter (MPI_Scatter), gather (MPI_Gather), and reduce (MPI_Reduce).

Blocking and Non-Blocking Operations: MPI operations can be blocking or non-blocking. Blocking operations, like MPI_Send and MPI_Recv, cause the calling process to wait until the communication is complete. Non-blocking operations, such as MPI_Isend and MPI_Irecv, allow the program to continue executing while the communication is in progress.

MPI Library: Open MPI provides a set of libraries and tools that implement the MPI standard. These libraries facilitate the development of parallel applications by providing a consistent interface for communication and synchronization.

MPI Compiler Wrapper: Open MPI includes compiler wrappers (mpicc, mpic++, mpifort, etc.) that simplify the compilation and linking of MPI applications. These wrappers automatically include the necessary MPI libraries and settings.

MPI Rank and Size: MPI ranks are unique identifiers assigned to each process within a communicator, ranging from 0 to (size-1), where size is the total number of processes in the communicator.

## Chapter III

### Part 1. Introduction to OpenMP

#### Task 1

Write a program that prints "Hello world!" from each process.

#### Task 2

Write a program that finds the maximum of an array using multithreading.

#### Task 3

Write a program that calculates Pi using the Monte Carlo method.

#### Task 4

Write a program that calculates the average of positive numbers in an array.

#### Task 5

Write a program that calculates the scalar product of vectors.

#### Task 6

Write a program that finds the maximum and minimum of a matrix.

#### Task 7

Write a program that multiplies a matrix by a vector, dividing data by columns.

#### Task 8

Write a program that implements Scatter and Gather using Send and Recv.

#### Task 9

Write a program that inverts an array.

#### Task 10

Write a program that calculates transfer time for different Sends.

#### Task 11

Write a program that implements cyclic data transfer.

### Part 2 - Bonus Part

#### Task 12

Write a program that implements circular number transfer for different communicators.

#### Task 13

Write a program that checks matrices for symmetry.

#### Task 14

Write a program that sorts an array using the even-odd permutation method.

### Part 3 - Midterm

#### Task 15

Write a program that implements matrix multiplication using Cannon's algorithm.

#### Task 16

Write a program that implements matrix multiplication using Fox's algorithm.

#### Task 17

Write a program that implements matrix sorting using Shell's algorithm.

#### Task 18

Write a program that implements the Gauss method.

#### Task 19

Write a program that implements quicksort with a pivot element selection.

#### Task 20

Write a program that implements the Floyd-Warshall algorithm.

#### Task 21

Write a program that implements Kruskal's algorithm.

#### Task 22

Write a program that implements Prim's algorithm.

#### Task 23

Write a program that implements Kernighan-Lin algorithm.
