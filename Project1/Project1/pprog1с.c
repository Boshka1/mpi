#include <stdio.h>
#include <mpi.h>
#define N 10

int proc_count, proc_this;

int main(int argc, char** argv)
{

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);
	double A[N];

	for (int i = 0; i < N; i++)
		A[i] = i;
	double sum = 0;
	for (int i = proc_this; i < N; i += proc_count)
	{
		sum += A[i];
	}
	printf("Process No_%d from %d: sum = %f\n", proc_this, proc_count, sum);




	MPI_Finalize();
	return 0;
}