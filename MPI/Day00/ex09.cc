#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sys/time.h>


void print_arr(std::string arr_name, int *arr, int world_size) {
    printf("%s = [%d", arr_name.c_str(), arr[0]);
    for (int i = 1; i < world_size; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n\n");
}

void init_random() {
    struct timeval time;
    gettimeofday(&time, (struct timezone *) 0);
    srand((int) time.tv_sec);
}

int main(int argc, char **argv) {
    int size = 20;
    int world_rank, world_size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int *arr;
    int *reversed_array;

    if (world_rank == 0) {
        init_random();
        arr = new int[size];
        reversed_array = new int[size];
    }

    int *noepp = new int[world_size];
    int *indexes = new int[world_size];
    int *rvrsd_inds = new int[world_size];

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

    int nProc = noepp[world_rank];

    int *buf = new int[nProc];

    if (world_rank == 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10;
        }
        print_arr("Array", arr, size);

        rvrsd_inds[world_size-1] = 0;
        for (int i = world_size - 2; i >= 0; i--) {
            rvrsd_inds[i] = rvrsd_inds[i+1] + noepp[i+1];
        }
    }

    MPI_Scatterv(arr, noepp, indexes, MPI_INT, buf, nProc, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < nProc / 2; i++) {
        int temp = buf[i];
        buf[i] = buf[nProc - i - 1];
        buf[nProc - i - 1] = temp;
    }

    MPI_Gatherv(buf, nProc, MPI_INT, reversed_array, noepp, rvrsd_inds, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        print_arr("Reversed", reversed_array, size);
        delete[] arr;
        delete[] reversed_array;
    }
    delete[] noepp;
    delete[] indexes;
    delete[] rvrsd_inds;
    delete[] buf;
    

    MPI_Finalize();
}
