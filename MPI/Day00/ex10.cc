#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>

void init_random() {
    struct timeval time;
    gettimeofday(&time, (struct timezone *) 0);
    srand((int) time.tv_sec);
}


int main(int argc, char **argv) {
    const int size = 100;
    int message_buffer_size = size * sizeof(int) + MPI_BSEND_OVERHEAD;
    int world_rank, world_size;
    int *sbuf = new int[size];
    int *rbuf = new int[size];
    int *buf = new int[message_buffer_size];
    double t1, t2;
    MPI_Request send_request;
    MPI_Request recv_request;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_rank == 0) {
        init_random();
        for (int i = 0; i < size; i++) {
            sbuf[i] = rand() % 10000;
        }
        printf("Array Length is %d\n", size);
    }

    if (world_rank == 0) {
        if (world_size == 1) {
            printf("Only one process, nothing to do\n");
            return 0;
        }

        t1 = MPI_Wtime();

        MPI_Send(sbuf, size, MPI_INT, 1, 2, MPI_COMM_WORLD);
        MPI_Recv(rbuf, size, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        t2 = MPI_Wtime();
        printf("Time taken with Send: %f \n", t2 - t1);

        t1 = MPI_Wtime();
        MPI_Ssend(sbuf, size, MPI_INT, 1, 3, MPI_COMM_WORLD);
        MPI_Recv(rbuf, size, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        t2 = MPI_Wtime();
        printf("Time taken with Ssend: %f \n", t2 - t1);

        t1 = MPI_Wtime();
        MPI_Buffer_attach(buf, message_buffer_size);
        MPI_Bsend(sbuf, size, MPI_INT, 1, 4, MPI_COMM_WORLD);
        MPI_Recv(rbuf, size, MPI_INT, 1, 4, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        t2 = MPI_Wtime();
        printf("Time taken with Bsend: %f \n", t2 - t1);
        MPI_Buffer_detach(buf, &message_buffer_size);
        free(buf);

        t1 = MPI_Wtime();
        MPI_Rsend(sbuf, size, MPI_INT, 1, 5, MPI_COMM_WORLD);
        MPI_Recv(rbuf, size, MPI_INT, 1, 5, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        t2 = MPI_Wtime();
        printf("Time taken with Rsend: %f \n", t2 - t1);

        t1 = MPI_Wtime();
        MPI_Isend(sbuf, size, MPI_INT, 1, 6, MPI_COMM_WORLD, &send_request);
        MPI_Irecv(rbuf, size, MPI_INT, 1, 6, MPI_COMM_WORLD, &send_request);
        MPI_Wait(&send_request, MPI_STATUS_IGNORE);
        t2 = MPI_Wtime();
        printf("Time taken with Isend: %f \n", t2 - t1);

    } else if (world_rank == 1) {
        MPI_Recv(rbuf, size, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        sbuf = rbuf;
        MPI_Send(sbuf, size, MPI_INT, 0, 2, MPI_COMM_WORLD);

        MPI_Recv(rbuf, size, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        sbuf = rbuf;
        MPI_Ssend(sbuf, size, MPI_INT, 0, 3, MPI_COMM_WORLD);

        MPI_Recv(rbuf, size, MPI_INT, 0, 4, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        MPI_Buffer_attach(buf, message_buffer_size);
        sbuf = rbuf;
        MPI_Bsend(sbuf, size, MPI_INT, 0, 4, MPI_COMM_WORLD);
        MPI_Buffer_detach(buf, &message_buffer_size);
        free(buf);

        MPI_Recv(rbuf, size, MPI_INT, 0, 5, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        sbuf = rbuf;
        MPI_Rsend(sbuf, size, MPI_INT, 0, 5, MPI_COMM_WORLD);

        MPI_Irecv(rbuf, size, MPI_INT, 0, 6, MPI_COMM_WORLD, &recv_request);
        sbuf = rbuf;
        MPI_Isend(sbuf, size, MPI_INT, 0, 6, MPI_COMM_WORLD, &recv_request);
        MPI_Wait(&recv_request, MPI_STATUS_IGNORE);
    }
    // printf("Process %d finished\n", world_rank);

    MPI_Finalize();

    return 0;
}