#!/bin/bash
#SBATCH --job-name=weak_mpi_all
#SBATCH --output=weak_mpi_all_%j.out
#SBATCH --error=weak_mpi_all_%j.err
#SBATCH --time=00:05:00      # 5 min is more than enough
#SBATCH --nodes=1
#SBATCH --ntasks=128         # allocate up to the cluster’s max (128)

module load mpi
export OMP_NUM_THREADS=1

N=10
for P in 64 128; do
  echo "=== MPI ranks: $P ==="
  srun --mpi=pmi2 -n $P ./optimizer $N
  echo
done

