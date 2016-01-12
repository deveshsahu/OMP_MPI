#include <iostream>
#include <stdlib.h>
#include "recscan.cpp"
#include <sys/time.h>
using namespace std;
void genericScan(void *X, int n, size_t l);

// the use must define this function to use genericScan
void userBinaryOperator( void *x1, void *x2){
	double *a = (double *) x1;
	double *b = (double *) x2;
  
  *a += *b;
}


int main( int argc, char **argv){	
	
	// problem setup
	int n=300000000;
	if(argc>1) n=atoi(argv[1]);
	double *x = new double[n];
	for(int i=0;i<n;i++) x[i] = 1;

	// print input
//	for(int i=0;i<n;i++) cout<<x[i]<<endl;

	// Declaring and starting clock
	struct timeval start,finish;
	double time_elapsed;
	gettimeofday(&start,NULL);
	
	// scan
	genericScan((void*) x,n,sizeof(double));

	//Evaluate time consumed
	gettimeofday(&finish,NULL);
	time_elapsed = (finish.tv_sec-start.tv_sec) + (finish.tv_usec-start.tv_usec)*1e-6;
	
	//print output
	// for(int i=0;i<n;i++) cout<<x[i]<<endl;

	// Print time taken
	 cout<<"\nTime elapsed ="<<time_elapsed<<" seconds...\n";

	// clean up
	free(x);
	return 0;
}
	




	


	



