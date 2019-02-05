#!/bin/sh
#SBATCH -J mmjob           		# job name
#SBATCH -o mmjob.o%j.out	       	# output and error file name (%j expands to jobID)
#SBATCH -N 1 				# no of nodes
#SBATCH -n 48             		# total number of mpi tasks requested
#SBATCH -p skx-dev	     		# queue (partition) -- normal, development, etc.
#SBATCH -t 02:00:00        		# run time (hh:mm:ss) -

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

./bin/drsteal_mod $size10 $base10 $t_count
./bin/drshare_mod $size10 $base10 $t_count

./bin/drsteal_mod $size11 $base11 $t_count
./bin/drshare_mod $size11 $base11 $t_count

./bin/drsteal_mod $size12 $base12 $t_count
./bin/drshare_mod $size12 $base12 $t_count

./bin/drsteal_mod $size13 $base13 $t_count
./bin/drshare_mod $size13 $base13 $t_count

./bin/drsteal_mod $size14 $base14 $t_count
./bin/drshare_mod $size14 $base14 $t_count

t_count=$((3))
for cor_number in {2..16}
	do
		t_c=$(($t_count*cor_number))
		./bin/drsteal_mod $size14 $base14 $t_c
		./bin/drshare_mod $size14 $base14 $t_c
done


echo "____________________________\n"

