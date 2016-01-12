#include <iostream>
#include <stdlib.h>
#include "genscan4.cpp"
#include <sys/time.h>
using namespace std;
void genericScan(void **X, int n, size_t l);

// the use must define this function to use genericScan
void userBinaryOperator( void **x1, void **x2){
	double **a = (double **) x1;
	double **b = (double **) x2;
	for (int i = 0;i<4;i++)
		*a[i] += *b[i];
}


int main( int argc, char **argv){	
	
	// problem setup
	int n=300000000;
	if(argc>1) n=atoi(argv[1]);
	double **x = new double*[n];
	for(int i=0;i<n;i++) 
		x[i] = new double [4];
	for(int i=0;i<n;i++) {
		x[i][0] = i%7;
		x[i][1] = i%2;
		x[i][2] = i%3;
		x[i][3] = i%5;
		}
		
	// print input
//	for(int i=0;i<n;i++) printf("%d ",x[i]); 	printf("\n");

	// Declaring and starting clock
	struct timeval start,finish;
	double time_elapsed;
	gettimeofday(&start,NULL);
	
	// scan
	genericScan((void**) x,n,4*sizeof(double));

	//Evaluate time consumed
	gettimeofday(&finish,NULL);
	time_elapsed = (finish.tv_sec-start.tv_sec) + (finish.tv_usec-start.tv_usec)*1e-6;
	
	
	//print output
//	for(int i=0;i<n;i++) printf("%d ",x[i]); 	printf("\n");

	// Print time taken
	 cout<<"\nTime elapsed ="<<time_elapsed<<" seconds...\n";

	// clean up
	free(x);
	return 0;
}
	
