#!/bin/sh
#SBATCH -J mmjob           		# job name
#SBATCH -o mmjob.o%j.out	       	# output and error file name (%j expands to jobID)
#SBATCH -N 1 				# no of nodes
#SBATCH -n 48             		# total number of mpi tasks requested
#SBATCH -p skx-dev	     		# queue (partition) -- normal, development, etc.
#SBATCH -t 02:00:00        		# run time (hh:mm:ss) -

size14=$((16384))

base14=$((256))

t_count=$((3))
for cor_number in {2..16}
	do
		t_c=$(($t_count*cor_number))
		./bin/cshare $size14 $base14 $t_c
		./bin/drsteal $size14 $base14 $t_c
		./bin/drshare $size14 $base14 $t_c
done


echo "____________________________\n"

