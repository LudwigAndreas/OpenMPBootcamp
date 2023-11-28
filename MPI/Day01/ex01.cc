#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sys/time.h>

void colored_print(std::string message, int color) {
    printf("\033[1;3%dm%s\033[0m\n", color, message.c_str());
}

void print_arr(std::string arr_name, int *arr, int size) {
    printf("%s = [%d", arr_name.c_str(), arr[0]);
    for (int i = 1; i < size; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n\n");
}

void init_random() {
    struct timeval time;
    gettimeofday(&time, (struct timezone *) 0);
    srand((int) time.tv_sec);
}

void check_result(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("\033[1;31mError: arr[%d] = %d < arr[%d] = %d\033[0m\n", i, arr[i], i - 1, arr[i - 1]);
            return;
        }
    }
    printf("\033[1;32mResult is correct\033[0m\n");

}

int* merge_arrays(int *arr1, size_t size1, int *arr2, size_t size2)
{
	int i, j, k;
	int *result;

    result = new int[size1 + size2];

	i = 0;
    j = 0;
    k = 0;
	while (i < size1 && j < size2) {
		if(arr1[i]<arr2[j]) {
			result[k] = arr1[i];
			i++; 
            k++;
		} else {
			result[k] = arr2[j];
			j++;
            k++;
		}
    }
	if (i == size1) {
		while (j < size2) {
			result[k] = arr2[j];
			j++;
            k++;
		}
    } else {
		while(i < size1)
		{
			result[k] = arr1[i];
			i++;
            k++;
		}
    }
	return result;
}

void shell_sort(int numbers[], int array_size)
{
    int i, j, increment, temp;
	increment = 3;
	while (increment > 0)
	{
		for (i=0; i < array_size; i++)
		{
			j = i;
			temp = numbers[i];
			while ((j >= increment) && (numbers[j-increment] > temp))
			{
				numbers[j] = numbers[j - increment];
				j = j - increment;
			}
			numbers[j] = temp;
		}
		if (increment/2 != 0)
			increment = increment/2;
		else if (increment == 1)
			increment = 0;
		else
			increment = 1;
	}
}

int main(int argc, char **argv)
{
	int *array;
	int *chunk;
	int *other;
	int received_size, arr_size = 140000;
	int world_rank, world_size;
	int size_of_chank;
	int i;
	int step;
    double time_start;
    double time_finish;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (world_rank == 0) {
		int remainder;
		size_of_chank = arr_size / world_size;
		remainder = arr_size % world_size;
		
        array = new int[arr_size + world_size - remainder];
        colored_print("Initializing array (" + std::to_string(arr_size) + " size)...", 4);
		init_random();
		for (i = 0; i < arr_size; i++)
			array[i] = rand() % 10000;
		if (remainder != 0) {
			for (i = arr_size; i < arr_size + world_size - remainder; i++)
  			   array[i] = 0;
			size_of_chank = size_of_chank + 1;
		}
	
        colored_print("Start parallel Shell sorting...", 4);
		time_start = MPI_Wtime();

		MPI_Bcast(&size_of_chank, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
        chunk = new int[size_of_chank];
		MPI_Scatter(array, size_of_chank, MPI_INT, chunk, size_of_chank, MPI_INT, 0, MPI_COMM_WORLD);
		shell_sort(chunk, size_of_chank);
	} else {
		MPI_Bcast(&size_of_chank, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
        chunk = new int[size_of_chank];
		MPI_Scatter(array, size_of_chank, MPI_INT, chunk, size_of_chank, MPI_INT, 0, MPI_COMM_WORLD);
		shell_sort(chunk, size_of_chank);
	}

	step = 1;
	while (step < world_size) {
		if (world_rank % (2 * step) == 0) {
			if(world_rank + step < world_size) {
				MPI_Recv(&received_size, 1, MPI_INT, world_rank + step, 0, MPI_COMM_WORLD, &status);
				
                other = new int[received_size];
				MPI_Recv(other, received_size, MPI_INT, world_rank + step, 0, MPI_COMM_WORLD, &status);
				chunk = merge_arrays(chunk, size_of_chank, other, received_size);
				size_of_chank = size_of_chank + received_size;
			}
		}
		else {
			int near = world_rank - step;
			MPI_Send(&size_of_chank, 1, MPI_INT, near, 0, MPI_COMM_WORLD);
			MPI_Send(chunk, size_of_chank, MPI_INT, near, 0, MPI_COMM_WORLD);
			break;
		}
		step = step * 2;
	}


	if (world_rank == 0) {
		time_finish = MPI_Wtime();

        colored_print("Elapsed time = " + std::to_string(time_finish - time_start) + " seconds", 6);
        check_result(chunk, arr_size);

        time_start = MPI_Wtime();

        colored_print("Start sequential Shell sorting...", 4);
        shell_sort(array, arr_size);

        time_finish = MPI_Wtime();

        colored_print("Elapsed time = " + std::to_string(time_finish - time_start) + " seconds", 6);
        check_result(array, arr_size);
	}
	MPI_Finalize();
}