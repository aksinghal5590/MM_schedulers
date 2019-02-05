#!/bin/sh
#SBATCH -J mmjob           	# job name
#SBATCH -o mmjob.o%j.out    # output and error file name (%j expands to jobID)
#SBATCH -N 1				# total no of nodes
#SBATCH -n 48              	# total number of mpi tasks requested per node
#SBATCH -p skx-dev	     	# queue (partition) -- normal, development, etc.
#SBATCH -t 02:00:00        	# run time (hh:mm:ss) -

size10=$((1024))
size11=$((2048))
size12=$((4096))
size13=$((8192))
size14=$((16384))

base10=$((256))
base11=$((256))
base12=$((256))
base13=$((256))
base14=$((256))

t_count=$((48))

	./bin/cshare  $size10 $base10 $t_count
	./bin/drsteal $size10 $base10 $t_count
	./bin/drshare $size10 $base10 $t_count

	./bin/cshare  $size11 $base11 $t_count
	./bin/drsteal $size11 $base11 $t_count
	./bin/drshare $size11 $base11 $t_count

	./bin/cshare  $size12 $base12 $t_count
	./bin/drsteal $size12 $base12 $t_count
	./bin/drshare $size12 $base12 $t_count

	./bin/cshare  $size13 $base13 $t_count
	./bin/drsteal $size13 $base13 $t_count
	./bin/drshare $size13 $base13 $t_count

	./bin/cshare  $size14 $base14 $t_count
	./bin/drsteal $size14 $base14 $t_count
	./bin/drshare $size14 $base14 $t_count

echo "____________________________\n"

