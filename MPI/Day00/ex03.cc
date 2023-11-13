#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double calculate_pi_sequential() {
  double niter = 10000000;
  double x,y;
  int i;
  int count = 0;
  double z;
  double pi;
  srand(time(NULL));

  for (int i = 0; i < niter; ++i) {
    x = (double) random() / RAND_MAX;
    y = (double) random() / RAND_MAX;
    z = sqrt((x * x) + (y * y));
    if (z <= 1)
      ++count;
  }
  return ((double) count / (double) niter) * 4.0;
}

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("you need to pass 1 arguments.\n");
    printf("Usage: mpiexec ex03 <use sequential execution>\n");
  }

  int my_rank;  
  int rank;
  int num_proc;
  int sequential;
  MPI_Status   status;

  MPI_Init(&argc, &argv);     
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  if (my_rank == 0) {
    sequential = atoi(argv[1]);
    array_len = atoi(argv[2]);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    quotient = array_len / num_proc;
    rem = array_len % num_proc;

    generate_data(search_array,array_len);
  
    if (sequential)
      printf("The sequential search gives %d\n",
              find_max(search_array,array_len));

    for (rank=1; rank < rem; ++rank){
        sub_len = quotient+1;
        sub_start = rank*quotient+rank;
        MPI_Send(&sub_len,1,MPI_INT,rank,0,MPI_COMM_WORLD);
        MPI_Send(&(search_array[sub_start]),sub_len, MPI_INT, 
        rank, 0, MPI_COMM_WORLD);
    }
    for (rank=rem; rank < num_proc; ++rank){
        sub_len = quotient;
        sub_start = rank*quotient+rem;
        MPI_Send(&sub_len,1,MPI_INT,rank,0,MPI_COMM_WORLD);
        MPI_Send(&(search_array[rank*quotient+rem]),quotient, 
                  MPI_INT, rank, 0, MPI_COMM_WORLD);
		 }

    if (rem==0)
      sub_len=quotient;
    else 
      sub_len=quotient+1;
    global_max = find_max(search_array,quotient+1);

    for (rank=1;rank<num_proc;++rank){
          MPI_Recv(&local_max,1,MPI_INT,MPI_ANY_SOURCE,0,
                        MPI_COMM_WORLD, &status);
          if (local_max > global_max)
              global_max = local_max;
    }
    printf("The parallel search gives %d\n", global_max);
  } else {
    MPI_Recv(&sub_len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		
    MPI_Recv(search_array,sub_len,MPI_INT,0,0,MPI_COMM_WORLD,
				 &status);
    my_max = find_max(search_array,sub_len);
    MPI_Send(&my_max,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }
         
               
  MPI_Finalize();
  return 0;   
}
