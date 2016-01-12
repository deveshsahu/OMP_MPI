#include <iostream>
#include <omp.h>
using namespace std;

void userBinaryOperator(void **input1andOutput, void **input2);

#define ubop(x1,x2) userBinaryOperator( (void **) (x1), (void **) (x2) );

char* seqscan(char* a,int N){
char *s1,*s2;
s1 = new char[N/2];
s2 = new char[N/2];
if (N/2>0){
s1 = seqscan(&a[0],N/2);
s2 = seqscan(&a[N/2],N/2);	// Check if n/2 is working fine
}
for (int j=0;j<N/2;j++){
	s2[j] = s2[j] + s1[N];
	}
char* s;
s = new char[N];

for(int j=0;j<N/2;j++)
	s[j] = s1[j];

for(int j=N/2;j<N;j++)
	s[j] = s2[j-N/2];
	
return s;
}
char** parscan(char** a,int N){
char** s;
*s = new char[N];
for (int i=0;i<N;i++)
	s[i] = new char[4];
//parallel do
omp_set_num_threads(6);
#pragma omp parallel
{
char **s1,**s2;
*s1 = new char[N/2];
for (int i = 0;i<N/2;i++)
	s1[i] = new char[4];
*s2 = new char[N/2];
for (int i = 0;i<N/2;i++)
	s2[i] = new char [4];
if (N/2>0){
//int t = omp_get_numthreads();
	s1 = parscan(&a[0],N/2);
	s2 = parscan(&a[N/2],N/2);
}

//parallel do ends

//parallel for begins
#pragma omp  for
for (int j=0;j<N/2;j++){
	for(int k=0;k<4;k++)
		s2[j][k] = s2[j][k] + s1[N][k];
	}
//parallel for ends

#pragma omp for
for(int j=0;j<N/2;j++)
	for(int k=0;k<4;k++)
		s[j][k] = s1[j][k];
#pragma omp for
for(int j=N/2;j<N;j++)
	for (int k=0;k<4;k++)
		s[j][k] = s2[j-N/2][k];
	}	
return s;
}
	
void genericScan(void **X, int n, size_t l)
{
	int i;
	char **c = (char **)X;
	#pragma omp for
	for (i=1;i<n;i++)	
		ubop( (void **)(c+i*l),  (void **)(c+l*(i-1)) ); 
	
	c = parscan(c,n);
		
}


