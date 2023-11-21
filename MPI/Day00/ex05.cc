#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    const int size = 20;
    int world_rank, world_size;
    int a[size];
    int b[size];
    int res = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_rank == 0)
    {
        for (int i = 0; i < size; i++) {
            a[i] = rand() % 100 * (rand() % 2 ? 1 : -1);
            b[i] = rand() % 10;
            if (i == 0) {
                printf("a = [%d", a[i]);
            } else {
                printf(", %d", a[i]);
            }
        }
        printf("]\n");
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                printf("b = [%d", b[i]);
            } else {
                printf(", %d", b[i]);
            }
        }
        printf("]\n");
    }

    int *cnts = new int[world_size];
    int *inds = new int[world_size];

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

    int nProc = cnts[world_rank];
    int *aProc = new int[nProc];
    int *bProc = new int[nProc];

    MPI_Scatterv(a, cnts, inds, MPI_INT, aProc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);
    MPI_Scatterv(b, cnts, inds, MPI_INT, bProc, nProc, MPI_INT,
                 0, MPI_COMM_WORLD);

    int sum = 0;
    for (int i = 0; i < nProc; i++)
        sum += aProc[i] * bProc[i];

    printf("proccess %d, sum = %d\n", world_rank, sum);

    MPI_Allreduce(&sum, &res, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (!world_rank) {
        printf("dot product of vectors is %d", res);
    }

    MPI_Finalize();
}
