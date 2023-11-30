#!/bin/bash
#SBATCH --ntasks=64
#SBATCH --nodes=4
#SBATCH --output=%x.o%j
#SBATCH --time=96:00:00
##SBATCH --account=csigeneral
srun ../../../../bin/LINUX64/nwchem dplot_dft_prep.nw 2>&1 > dplot_dft_prep.out2

