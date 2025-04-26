#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>
#include "secret_function.h"

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc<2) {
    if (rank==0) fprintf(stderr,"Usage: %s N\n",argv[0]);
    MPI_Finalize();
    return 1;
  }
  int N = atoi(argv[1]);
  double t0 = omp_get_wtime();

  // Monte Carlo sampling
  double local_min = 1e308;
  unsigned int seed = (unsigned)time(NULL) ^ rank;
  for (int i=0; i<N; i++) {
    double x1 = -512.0 + (rand_r(&seed)/(double)RAND_MAX)*1024.0;
    double x2 = -512.0 + (rand_r(&seed)/(double)RAND_MAX)*1024.0;
    double f  = secret_function(x1,x2);
    printf("Rank %d sample %d f = %e\n", rank, i+1, f);
    if (f < local_min) local_min = f;
  }
  printf("Rank %d local min = %e\n", rank, local_min);

  double tr0 = omp_get_wtime();
  double global_min;
  MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
  double tr1 = omp_get_wtime();
  double t1  = omp_get_wtime();

  if (rank==0) {
    printf("Global min = %e\n", global_min);
    printf("Total time     = %f s\n", t1 - t0);
    printf("Reduction time = %f s\n", tr1 - tr0);
  }
  MPI_Finalize();
  return 0;
}

