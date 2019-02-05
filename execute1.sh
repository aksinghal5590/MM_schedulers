#!/bin/sh
#SBATCH -J mmjob           # job name
#SBATCH -o mmjob.o%j.out       # output and error file name (%j expands to jobID)
#SBATCH -n 272              # total number of mpi tasks requested
#SBATCH -p skx-dev      # queue (partition) -- normal, development, etc.
#SBATCH -t 02:00:00        # run time (hh:mm:ss) -

size0=$((1024))
base=$((32))
t_count=$((272))

./bin/mmprogram $size0 $base $t_count 1 1
