#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Get_input(int argc, char* argv[], int myRank, long* totalNumTosses_p){
	if (myRank == 0) {
		if (argc!= 2){
      fprintf(stderr, "usage: mpirun -np <N> %s <number of tosses> \n", argv[0]);
      fflush(stderr);
      *totalNumTosses_p = 0;
		} else {
			*totalNumTosses_p = atoi(argv[1]);
		}
	}
	MPI_Bcast(totalNumTosses_p, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	
    if (*totalNumTosses_p == 0) {
        MPI_Finalize();
        exit(-1);
    }
}

long Toss (long processTosses, int myRank){
	long toss, numberInCircle = 0;        
	double x,y;
	unsigned int seed = (unsigned) time(NULL);
	srand(seed + myRank);

	for (toss = 0; toss < processTosses; toss++) {
    x = rand_r(&seed) / (double) RAND_MAX;
    y = rand_r(&seed) / (double) RAND_MAX;
    if((x * x + y * y) <= 1.0) 
      numberInCircle++;
  }
  return numberInCircle;
}

int main(int argc, char** argv) {
  int world_rank, world_size;
  long totalNumTosses, numProcessTosses, processNumberInCircle, totalNumberInCircle;
  double start, finish, loc_elapsed, elapsed, piEstimate;
  double PI25DT = 3.141592653589793238462643;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  
  Get_input(argc, argv, world_rank, &totalNumTosses);
  
  numProcessTosses = totalNumTosses/world_size; 
  
  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();
  processNumberInCircle = Toss(numProcessTosses, world_rank);
  finish = MPI_Wtime();
  loc_elapsed = finish - start;
  MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 

  MPI_Reduce(&processNumberInCircle, &totalNumberInCircle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if (world_rank == 0) {
    piEstimate = (4*totalNumberInCircle)/((double) totalNumTosses);
    printf("Elapsed time = %f seconds \n", elapsed);
    printf("Pi is approximately %.16f, Error is %.16f\n", piEstimate, fabs(piEstimate - PI25DT));
  }
  MPI_Finalize(); 
  return 0;
}  

