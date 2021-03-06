#include"bsearch.cpp"
#include<iostream>
using namespace std;
int n=100;

double * a;
int out;
// KEY TO SEARCH
double key = 10;

// NUMBER OF PROCESSORS
int p = 6;
struct timeval start,finish;
double time_elapsed;

int main(int arc,char* argv[]){

 int myrank,size,out1,out2;
 if (argv[2])
 	n = atoi(arg[2]);
int mid;
a = new double[n];
for (int i = 0;i<n;i++){
		if (i < n/2)
			a[i] = i+1;
	 	else
	 		a[i] = 5*n-2*i;
	 	}
 	sort(a,n);

	gettimeofday(&start,NULL);
	mid = n/2;
	if(key>= a[0] && key<=a[n-1])
		out1 =  bsearch(key,&a[mid],n/2,p);
	else
		out2 =  bsearch(key,a,n/2,p);
		
	if(out1>0 || out2>0)
		out =1;
	else 
		out = -1

	}	


gettimeofday(&finish,NULL);
time_elapsed = (finish.tv_sec-start.tv_sec) + (finish.tv_usec-start.tv_usec)*1e-6;

if (out<0) 
cout<<"\nNot found";
else
cout<<"\nFound";
cout<<"\nTime taken= "<<time_elapsed<<endl;

MPI_Finalize();
}
