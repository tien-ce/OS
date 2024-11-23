#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
long long int n; 
int num_Thread;
long long int *partial_sum;
long long int race_condition_sum = 0;
void *thread_sum(void *arg){
	int thread_id = *(int*) arg;
	long long int start = (n /num_Thread) * thread_id +1;
	long long int end = (thread_id == num_Thread - 1) ? n : (n / num_Thread) * (thread_id + 1);

	partial_sum[thread_id] = 0;
	
	long long int i ;
	for (i=start ; i<=end;i++){
		partial_sum[thread_id] += i;
		/*race_condition_sum +=i;*/
	}
	free(arg);
	return NULL;	
}

int main(int argc,char *argv[]){
	clock_t start,end;
	start = clock();
	num_Thread = atoll(argv[1]);
	n = atoll(argv[2]);
	partial_sum = malloc((num_Thread + 1)* sizeof(long long int));
	pthread_t threads[num_Thread];
	int i ;
	for( i = 0 ; i<num_Thread;i++){
		int *thread_id = malloc(sizeof(int));
		*thread_id = i;
		if(pthread_create(&threads[i],NULL,thread_sum,thread_id)!=0)
		{
			printf("Failed with create thread");
			return 1;
		}
	}
	for (i = 0; i < num_Thread; i++) {
	pthread_join(threads[i], NULL);
	}

	long long int total_sum = 0;
	for (i = 0 ;i<num_Thread;i++){
		total_sum +=partial_sum[i];
	}
	end = clock();
	double speed = ((double)(end - start)/CLOCKS_PER_SEC);	
	//printf("Sum from 1 to %lld with %d thread is %lld\n",n,num_Thread,race_condition_sum);
	printf("Sum from 1 to %lld with %d thread is %lld\n",n,num_Thread,total_sum);
	printf("Time is %f\n",speed);
	free(partial_sum);
	return 0;
}
