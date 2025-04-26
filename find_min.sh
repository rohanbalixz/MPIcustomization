#!/bin/bash
#SBATCH --job-name=find_min
#SBATCH --output=find_min_%j.out
#SBATCH --error=find_min_%j.err
#SBATCH --nodes=1
#SBATCH --ntasks=128
#SBATCH --time=00:23:00

module load mpi
export OMP_NUM_THREADS=1

# Each rank does 1 sample ⇒ total 128 samples ≥ 107
mpirun -np $SLURM_NTASKS ./optimizer 1

