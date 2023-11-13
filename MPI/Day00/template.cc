#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MASTER 0

void Get_input(int argc, char* argv[], int myRank, int* number){
	if (myRank == MASTER) {
		if (argc != 2){
      fprintf(stderr, "usage: mpirun -np <N> %s <number> \n", argv[0]);
      fflush(stderr);
      *number = 0;
		} else {
			*number = atoi(argv[1]);
		}
	}
	MPI_Bcast(number, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	
    if (*number == 0) {
        MPI_Finalize();
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int world_rank, world_size;
    double start, finish;
    int input;
  
    int ierr = MPI_Init(&argc, &argv);
    if (ierr != MPI_SUCCESS) {
		printf("MPI_Init failed: %d\n", ierr);
	}
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Get_input(argc, argv, world_rank, &input);
  
    MPI_Barrier(MPI_COMM_WORLD);
    if (world_rank == MASTER) {
        start = MPI_Wtime();
    }
    
    // Do some work

    if (world_rank == MASTER) {
        finish = MPI_Wtime();
        double elapsed = finish - start;
        printf("Runtime = %f seconds \n", elapsed);
    }  
    MPI_Finalize(); 
    return 0;
}  

