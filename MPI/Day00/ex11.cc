#include <string>
#include <sys/time.h>
#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>

void colored_print_message_send(int world_rank_sender, int world_rank_receiver, std::string message) {
    printf("\033[1;3%dmProcess %d sends to process %d: %s\033[0m\n", world_rank_sender + 1, world_rank_sender,
           world_rank_receiver, message.c_str());
}

void colored_print_message_recv(int world_rank_sender, int world_rank_receiver, std::string message) {
    printf("\033[1;3%dmProcess %d receives from process %d: %s\033[0m\n", world_rank_receiver + 1, world_rank_receiver,
           world_rank_sender, message.c_str());
}

void init_random() {
    struct timeval time;
    gettimeofday(&time, (struct timezone *) 0);
    srand((int) time.tv_sec);
}

int main(int argc, char **argv) {
    int size = 2;
    int world_rank, world_size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int *send = new int[2];
    int *recv = new int[2];

    int send_to = world_rank + 1;
    int recv_from = world_rank - 1;

    if (world_rank == 0) {
        recv_from = world_size - 1;
    }

    if (world_rank == world_size - 1) {
        send_to = 0;
    }

    if (world_rank == 0) {
        send[0] = size;
        send[1] = world_rank * size;
        MPI_Send(send, 2, MPI_INT, send_to, send_to, MPI_COMM_WORLD);
        colored_print_message_send(world_rank, send_to, std::to_string(send[0]) + ", " + std::to_string(send[1]));
    }
    if (world_rank != 0) {
        MPI_Recv(recv, 2, MPI_INT, recv_from, world_rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        colored_print_message_recv(recv_from, world_rank, std::to_string(recv[0]) + ", " + std::to_string(recv[1]));
        send[0] = recv[0] + world_rank;
        send[1] = recv[1] + world_rank;

        MPI_Send(send, 2, MPI_INT, send_to, send_to, MPI_COMM_WORLD);
        colored_print_message_send(world_rank, send_to, std::to_string(send[0]) + ", " + std::to_string(send[1]));
    }

    if (world_rank == 0) {
        MPI_Recv(recv, 2, MPI_INT, recv_from, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        colored_print_message_recv(recv_from, world_rank, std::to_string(recv[0]) + ", " + std::to_string(recv[1]));
    }

    MPI_Finalize();
}
