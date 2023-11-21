#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_LEN 100000

int find_max(int arr[], size_t len) {
    int i;
    int max;
    if (len == 0) 
        return 0;
    else if (len < 2) {
        return arr[0];
    }
    max = arr[0];
    for (i = 1; i < len; ++i) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void generate_data(int arr[], size_t len) {
  int i;
  struct timeval time;
  gettimeofday(&time, (struct timezone *) 0);
  srand((int) time.tv_sec);

  for (i = 0; i < len; ++i) {
      arr[i] = rand();
  }
}

int main(int argc, char** argv) {

  int my_rank;  
  int rank;
  int num_proc;
  int array_len;
  int sequential;
  int quotient;
  int rem;
  int sub_start;
  int sub_len;
  int search_array[MAX_LEN];
  int my_max;
  int global_max;
  int local_max;
  MPI_Status   status;

  MPI_Init(&argc, &argv);     
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  if (my_rank == 0) {

    if (argc != 3) {
      printf("you need to pass 2 arguments.\n");
      printf("Usage: mpiexec ex02 <use sequential execution> <array size>\n");
      MPI_Finalize();
      return 0;
    }

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
