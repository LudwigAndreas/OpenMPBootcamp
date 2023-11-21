#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>

int main(int argc, char **argv) {
    const int size = 8;
    int world_rank, world_size;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int **matrix;
    int max, min;

    int *num_elements_per_proc = new int[world_size];
    int *index_start = new int[world_size];

    if (world_rank == 0) {
        matrix = new int *[size];
    }

    int rest = size;
    int k = size / world_size;
    num_elements_per_proc[0] = k * size;
    index_start[0] = 0;

    for (int i = 1; i < world_size; ++i) {
        rest -= k;
        k = rest / (world_size - i);
        num_elements_per_proc[i] = k * size;
        index_start[i] = index_start[i - 1] + num_elements_per_proc[i - 1];
    }

    int size_per_rank = num_elements_per_proc[world_rank];
    int *send_arr = new int[size * size];

    int *buf = new int[size_per_rank];


    if (world_rank == 0) {
        struct timeval time;
        gettimeofday(&time, (struct timezone *) 0);
        srand((int) time.tv_sec);

        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = rand() % 100;
                printf("%d ", matrix[i][j]);
                send_arr[size * i + j] = matrix[i][j];
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Scatterv(send_arr, num_elements_per_proc, index_start, MPI_INT, buf, size_per_rank, MPI_INT,
                    0, MPI_COMM_WORLD);

    int local_max = INT32_MIN;
    int local_min = INT32_MAX;

    for (int i = 0; i < size_per_rank; ++i) {
        if (buf[i] < local_min)
            local_min = buf[i];
        if (buf[i] > local_max)
            local_max = buf[i];
    }

    MPI_Allreduce(&local_max, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&local_min, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("min = %d, max = %d\n", min, max);

        for (int i = 0; i < size; ++i) {
            delete[] matrix[i];
        }
        delete matrix;
    }
    delete[] buf;
    delete[] send_arr;
    delete[] num_elements_per_proc;
    delete[] index_start;

    MPI_Finalize();
}
