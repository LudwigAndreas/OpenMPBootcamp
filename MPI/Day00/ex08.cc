#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include <string>

void print_arr(std::string arr_name, int *arr, int size) {
    printf("%s = [%d", arr_name.c_str(), arr[0]);
    for (int i = 1; i < size; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n\n");
}

int main(int argc, char **argv) {
    const int size = 20;
    int world_rank, world_size;
    int *arr = new int[size];
    int *res_arr = new int[size];

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Number of elements per process
    int *noepp = new int[world_size];
    // Indexes 
    int *indexes = new int[world_size];

    int rest = size;
    int k = size / world_size;
    noepp[0] = k;
    indexes[0] = 0;

    for (int i = 1; i < world_size; i++) {
        rest -= k;
        k = rest / (world_size - i);
        noepp[i] = k;
        indexes[i] = indexes[i - 1] + noepp[i - 1];
    }

    int num_proc = noepp[world_rank];
    int *buf = new int[num_proc];

    if (world_rank == 0) {
        struct timeval time;
        gettimeofday(&time, (struct timezone *) 0);
        srand((int) time.tv_sec);

        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10;
        }
        print_arr("Array", arr, size);

        for (int i = 0; i < world_size; i++) {
            int *send_buf = new int[noepp[i]];
            for (int j = 0; j < noepp[i]; j++) {
                send_buf[j] = arr[indexes[i] + j];
            }
            if (i == 0) {
                buf = send_buf;
            } else {
                MPI_Send(send_buf, noepp[i], MPI_INT, i, i, MPI_COMM_WORLD);
            }
        }
    }

    if (world_rank != 0) {
        MPI_Recv(buf, num_proc, MPI_INT, 0, world_rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    }

    printf("proccess number %d\n", world_rank);
    print_arr("buf" , buf, num_proc);


    if (world_rank != 0) {
        MPI_Send(buf, num_proc, MPI_INT, 0, world_rank + 10, MPI_COMM_WORLD);
    } else {
        for (int i = 0; i < num_proc; i++) {
            res_arr[i] = buf[i];
        }
    }

    if (world_rank == 0) {
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(buf, noepp[i], MPI_INT, i, i + 10, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            for (int j = 0; j < noepp[i]; j++) {
                res_arr[indexes[i] + j] = buf[j];
            }
        }

        print_arr("Result", res_arr, size);
    }
    MPI_Finalize();
}
