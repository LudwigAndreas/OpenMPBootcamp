#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    const int size = 100;
    int world_rank, world_size;
    int array[size];
    int temp[2];
    int res[2];

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_rank == 0)
    {
        for (int i = 0; i < size; i++) {
            array[i] = rand() % 100 * (rand() % 2 ? 1 : -1);
            if (i == 0) {
                printf("array: [%d", array[i]);
            } else {
                printf("+ %d", array[i]);
            }
        }
        printf("]\n");
    }

    int* cnts = new int[world_size];
    int* inds = new int[world_size];

    int rest = size;
    int k = size / world_size;
    cnts[0] = k;
    inds[0] = 0;

    for (int i = 1; i < world_size; i++) {
        rest -= k;
        k = rest / (world_size - i);
        cnts[i] = k;
        inds[i] = inds[i - 1] + cnts[i - 1];
    }

    int  nProc = cnts[world_rank];
    int* aProc = new int[nProc];

    MPI_Scatterv(array, cnts, inds, MPI_INT, aProc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);

    int sum = 0;
    int count = 0;
    for (int i = 0; i < nProc; i++)
        if (aProc[i] > 0) {
            sum += aProc[i];
            count++;
        };

    temp[0] = count;
    temp[1] = sum;
    printf("proccess %d, sum = %d, count = %d\n", world_rank, temp[1], temp[0]);

    MPI_Reduce(temp, res, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double ans = res[1] / res[0];
        printf("avg is %f, sum = %d; count = %d", ans, res[1], res[0]);
    }

    MPI_Finalize();
}