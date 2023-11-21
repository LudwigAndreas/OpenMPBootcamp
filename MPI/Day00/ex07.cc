#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>

int main(int argc, char **argv) {
    const int size = 5;
    int world_rank, world_size;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int **matrix;
    int *vector;

    if (world_rank == 0) {
        matrix = new int *[size];
        vector = new int[size];
    }

    // Number of elements per process for vector
    int *noepp_vctr = new int[world_size];
    // Indexes for vector
    int *indexes_vctr = new int[world_size];

    // Number of elements per process for matrix
    int *noepp_mtrx = new int[world_size];
    // Indexes for matrix
    int *indexes_mtrx = new int[world_size];

    int rest = size;
    int k = size / world_size;
    noepp_mtrx[0] = k * size;
    indexes_mtrx[0] = 0;

    noepp_vctr[0] = k;
    indexes_vctr[0] = 0;

    for (int i = 1; i < world_size; i++) {
        rest -= k;
        k = rest / (world_size - i);
        noepp_mtrx[i] = k * size;
        indexes_mtrx[i] = indexes_mtrx[i-1] + noepp_mtrx[i-1];
        noepp_vctr[i] = k;
        indexes_vctr[i] = indexes_vctr[i-1] + noepp_vctr[i-1];
    }

    // Number of elements per process for matrix
    int n_proc_mtrx = noepp_mtrx[world_rank];
    // Number of elements per process for vector
    int n_proc_vctr = noepp_vctr[world_rank];

    int *buf_mtrx = new int[n_proc_mtrx];
    int *buf_vctr = new int[n_proc_vctr];

    int *send_arr = new int[size*size];

    if (world_rank == 0) {
        struct timeval time;
        gettimeofday(&time, (struct timezone *) 0);
        srand((int) time.tv_sec);

        for (int i = 0; i < size; i++) {
            vector[i] = rand() % 10;
            matrix[i] = new int[size];
            for (int j = 0; j < size; j++) {
                matrix[i][j] = rand() % 10;
                send_arr[size * j + i] = matrix[i][j];
            }
        }
    }

    MPI_Scatterv(send_arr, noepp_mtrx, indexes_mtrx, MPI_INT, buf_mtrx, n_proc_mtrx, MPI_INT,
                 0, MPI_COMM_WORLD);
    MPI_Scatterv(vector, noepp_vctr, indexes_vctr, MPI_INT, buf_vctr, n_proc_vctr, MPI_INT,
                 0, MPI_COMM_WORLD);

    int *temp_sum = new int[size];
    int *res_sum = new int[size];

    for (int i = 0; i < size; i++) {
        temp_sum[i] = 0;
        res_sum[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < n_proc_vctr; j++) {
            temp_sum[i] += buf_vctr[j] * buf_mtrx[size * j + i];
        }
    }

    MPI_Reduce(temp_sum, res_sum, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("matrix = [\n");
        for (int i = 0; i < size; i++) {
            printf("[%d", matrix[i][0]);
            for (int j = 1; j < size; j++) {
                printf(", %d", matrix[i][j]);
            }
            printf("],\n");
        }
        printf("]\n");
        printf("vector = [%d" , vector[0]);
        for (int j = 1; j < size; j++) {
            printf(", %d", vector[j]);
        }
        printf("]\n");
        printf("result = [%d", res_sum[0]);
        for (int i = 1; i < size; ++i) {
            printf(", %d", res_sum[i]);
        }
        printf("]\n");

        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] vector;
    }
    delete[] buf_mtrx;
    delete[] buf_vctr;
    delete[] send_arr;
    delete[] temp_sum;
    delete[] res_sum;
    delete[] noepp_mtrx;
    delete[] indexes_mtrx;
    delete[] noepp_vctr;
    delete[] indexes_vctr;

    MPI_Finalize();
}
