all:scan run

CC=g++

scan:scan.o genscan.o
	@g++ scan.cpp -o scan -fopenmp

run:scan
	@./scan 1000000

clean:
	@/bin/rm -rf *.o	
