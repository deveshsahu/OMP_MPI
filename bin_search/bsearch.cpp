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
