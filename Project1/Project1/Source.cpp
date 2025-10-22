//#include <stdio.h>
//#include <mpi.h>
//int proc_count, proc_this;
//
//int main(int argc, char** argv)
//{
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
//	MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);
//
//	printf("Hello, I`m processor No_%d from %d\n", proc_this, proc_count);
//
//	MPI_Finalize();
//	return 0;
//}

//#include <stdio.h>
//#include <mpi.h>
//#define N 10
//
//int proc_count, proc_this;
//
//int main(int argc, char** argv)
//{
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
//	MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);
//	double A[N];
//
//	for (int i = 0; i < N; i++)
//		A[i] = i;
//	double sum = 0;
//	int block_size = (N + proc_count - 1) / proc_count;
//	int start = proc_this * block_size;
//	int end = start + block_size;
//	if (end > N) {
//		end = N;
//	}
//	for (int i = start; i < end; i++) {
//		sum += A[i];
//	}
//
//	printf("Process No_%d from %d: sum = %f\n", proc_this, proc_count, sum);
//
//
//
//	MPI_Finalize();
//	return 0;
//}


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