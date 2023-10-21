#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --output=%x.o%j
#SBATCH --time=24:00:00
##SBATCH --account=csigeneral
srun ../../../bin/LINUX64/nwchem 1fme_dynamics.nw 2>&1 > 1fme_dynamics.out

