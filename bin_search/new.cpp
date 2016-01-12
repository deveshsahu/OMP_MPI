#include<iostream>
#include<omp.h>
#include<cstdlib>
#include<sys/time.h>
using namespace std;
//#include<mpi.h>

int compare (const void * a, const void * b){
	double ua = *((double*)a);
	double ub = *((double*)b);
	if (ua>ub)
	 return 1;
	else 
	 return -1;
	}
void sort(double* a,int n){
	qsort(a,n,sizeof(double),compare);
	}
	
int bsearch(double key,double *a,int n,int p){
// Sort the arrray first

 int t = omp_get_num_threads();
 int id = omp_get_thread_num();
 int b = n/p;
 int start,end,mid,j=-1;
 int result=-1;
 #pragma omp parallel num_threads(p)
 #pragma omp parallel for
 for(int i = 1;i<=p;i++){
 	start = (i-1)*b;
 	end = i*b-1;
 	if(start<n){
 		if((end>n) || (id ==t-1 && end<n-1))
 			end = n-1;
 		if(key>= a[start] && key<=a[end]){
 			mid = (start+end+1)/2;
	 		if(b==1 && key==a[mid])
 				result = 1;
 			else if (key>= a[start] && key<a[mid])
 				bsearch(key, &a[start],b/2,p);
			else {
				bsearch(key, &a[mid],b/2,p);
				}
							
			}
		else
			result = -10;
	}
 }
return result;
}

#include<mpi.h>
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
int mid;
MPI_Init (NULL,NULL);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Status *status;
if(myrank==0){
a = new double[n];
for (int i = 0;i<n;i++){
		if (i < n/2)
			a[i] = i+1;
	 	else
	 		a[i] = 5*n-2*i;
	 	}
 	sort(a,n);

	gettimeofday(&start,NULL);
	if(key>= a[0] && key<=a[n-1]){
		 mid = n/2;
	MPI_Send(a,n/2,MPI_DOUBLE,1,1,MPI_COMM_WORLD);
	out1 =  bsearch(key,&a[mid],n/2,p);
	MPI_Recv(&out2,1,MPI_INT,1,2,MPI_COMM_WORLD,status);
	if(out1>0 || out2>0)
		out =1;
	else 
		out = -1;
	}
	else
		out = -1;
}
else{
	MPI_Recv(a,n/2,MPI_DOUBLE,0,1,MPI_COMM_WORLD,status);
	out2 =  bsearch(key,a,n/2,p);
	MPI_Send(&out2,1,MPI_INT,0,2,MPI_COMM_WORLD);
}	

if(myrank==0){
gettimeofday(&finish,NULL);
time_elapsed = (finish.tv_sec-start.tv_sec) + (finish.tv_usec-start.tv_usec)*1e-6;

if (out<0) 
cout<<"\nNot found";
else
cout<<"\nFound";
cout<<"\n Time taken= "<<time_elapsed<<endl;
}
MPI_Finalize();
}
