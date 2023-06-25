#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --output=%x.o%j
#SBATCH --time=36:00:00
##SBATCH --account=csigeneral
srun ../../../bin/LINUX64/nwchem 1byz_dynamics.nw 2>&1 > 1byz_dynamics.out

