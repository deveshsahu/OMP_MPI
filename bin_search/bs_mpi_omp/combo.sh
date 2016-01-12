mpic++ -fopenmp find.cpp
export OMP_NUM_THREADS=6
export KMP_AFFINITY=compact
mpirun tacc_affinity -np 2 ./a.out
