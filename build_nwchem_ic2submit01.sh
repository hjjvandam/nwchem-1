#!/bin/bash
module load cuda/12.2
module load python/3.11-anaconda-2023.07
module load gcc/12.3.0
module load openmpi/4.1.5
export NWCHEM_MODULES="smallqm"
export ARMCI_NETWORK=MPI-TS
export USE_INTERNALBLAS=Y
./contrib/distro-tools/build_nwchem $1
