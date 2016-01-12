all:scan run

CC=mpicc

scan:scan.o genscan.o
	@mpicc combo.cpp -o search -fopenmp

run:scan
	@mpirun -np 2 search

clean:
	@/bin/rm -rf *.o	
