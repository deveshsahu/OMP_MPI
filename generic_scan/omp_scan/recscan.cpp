void userBinaryOperator(void *input1andOutput, void *input2);
#define ubop(x1,x2) userBinaryOperator( (void *) (x1), (void *) (x2) );

char* rec_scan(char *a,int n){
	char *s = new char[n];
	if(n == 1){
		s[0] = a[0];
		return s;
		}
	char* b = new char[n/2];
	int i;
	#pragma omp for 
	for( i = 0;i<=n/2-1;++i)
		b[i] = a[2*i] + a[2*i+1];
		
	char* c = new char[n/2];
	c = rec_scan(b,n/2);
	
	s[0] = a[0];
	#pragma omp for
	for ( i = 1;i<=n-1;i++){
		if (i%2 == 0)
			s[i] = c[i/2];
		else
			s[i] = c[i/2] + a[i];
	}
	return s;
}

void genericScan(void *X, int n, size_t l)
{
	int i;
	char *c = (char *)X;

	for (i=1;i<n;i++)	
		ubop( (void *)(c+i*l),  (void *)(c+l*(i-1)) ); 
	
	c = rec_scan(c,n);
		
}


