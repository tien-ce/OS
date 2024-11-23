#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long long int sum_serial(long long int n){
	long long int sum = 0;
	long long int i;
	for( i = 0;i<=n;i++){
		sum+=i;
	}
	return sum;
}
int main(int argc, char*argv[]){
	clock_t start,end;
	start = clock();
	long long int n = atoll(argv[1]);
	long long int result = sum_serial(n);
	end = clock();
	printf("Sum from 1 to %lld is %lld\n",n,result);
	double speed = ((double)(end - start)/CLOCKS_PER_SEC );
	printf("Time with single thread is %f\n",speed);
	return 0 ;
}
