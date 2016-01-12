#include <iostream>
#include <stdlib.h>
#include "genscan.cpp"
#include <sys/time.h>
using namespace std;
void genericScan(void *X, int n, size_t l);

// the use must define this function to use genericScan
void userBinaryOperator( void *x1, void *x2){
	int *a = (int *) x1;
	int *b = (int *) x2;
  
  *a += *b;
}


int main( int argc, char **argv){	
	
	// problem setup
	int n=10;
	if(argc>1) n=atoi(argv[1]);
	int **x = new int*[n];
	for(int i=0;i<n;i++) 
		x[i] = new int [4];
	for(int i=0;i<n;i++) {
		x[i][0] = i%7;
		x[i][1] = i%2;
		x[i][2] = i%3;
		x[i][3] = i%5;
		}
		
	int *a1,*a2,*a3,*a4;
	a1 = new int[n];
	a2 = new int[n];
	a3 = new int[n];
	a4 = new int[n];
	
	for(int i=0;i<n;i++) {
		a1[i]=x[i][0] ;
		a2[i]=x[i][1] ;
		a3[i]=x[i][2] ;
		a4[i]=x[i][3];
		}		
	// print input
//	for(int i=0;i<n;i++) printf("%d ",x[i]); 	printf("\n");

	// Declaring and starting clock
	struct timeval start,finish;
	double time_elapsed;
	gettimeofday(&start,NULL);
	
	// scan
	genericScan((void*) a1,n,sizeof(int));
	genericScan((void*) a2,n,sizeof(int));
	genericScan((void*) a3,n,sizeof(int));
	genericScan((void*) a4,n,sizeof(int));

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
	
