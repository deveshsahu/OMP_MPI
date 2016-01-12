load module intel
g++ -fopenmp scan.cpp
KMP_AFFINITY=compact OMP_NUM_THREADS=6 ./a.out   # all threads in one socket
