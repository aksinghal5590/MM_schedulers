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

for papi in {1..3}
do
	./bin/cshare_p  $size10 $base10 $t_count $papi
	./bin/drsteal_p $size10 $base10 $t_count $papi
	./bin/drshare_p $size10 $base10 $t_count $papi
done

for papi in {1..3}
do
	./bin/cshare_p  $size11 $base11 $t_count $papi
	./bin/drsteal_p $size11 $base11 $t_count $papi
	./bin/drshare_p $size11 $base11 $t_count $papi
done

for papi in {1..3}
do
	./bin/cshare_p  $size12 $base12 $t_count $papi
	./bin/drsteal_p $size12 $base12 $t_count $papi
	./bin/drshare_p $size12 $base12 $t_count $papi
done

for papi in {1..3}
do
	./bin/cshare_p  $size13 $base13 $t_count $papi
	./bin/drsteal_p $size13 $base13 $t_count $papi
	./bin/drshare_p $size13 $base13 $t_count $papi
done

for papi in {1..3}
do
	./bin/cshare_p  $size14 $base14 $t_count $papi
	./bin/drsteal_p $size14 $base14 $t_count $papi
	./bin/drshare_p $size14 $base14 $t_count $papi
done

echo "____________________________\n"

