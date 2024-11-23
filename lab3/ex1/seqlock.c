#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "seqlock.h"  /* TODO implement this header file */
void pthread_seqlock_init(pthread_seqlock_t* rw){
	rw->seq = 0;
	pthread_mutex_init(&rw->lock, NULL);
}
void pthread_seqlock_wrlock(pthread_seqlock_t* rw){
	pthread_mutex_lock(&rw->lock);
	rw->seq++;
}

void pthread_seqlock_wrunlock(pthread_seqlock_t *rw){
	rw->seq ++;
	pthread_mutex_unlock(&rw->lock);
}

unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw){
	unsigned seq = rw->seq;
	do{
		seq= rw->seq;	
	}while(seq!=rw->seq);
	return seq;
}

unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw){
	return rw->seq;
}
int val = 0;
pthread_seqlock_t lock;
void* writer(){
	pthread_seqlock_wrlock(&lock);
	val++;
	printf("Change value = %d\n",val);
	pthread_seqlock_wrunlock(&lock);
	return NULL;
}

void* reader() {
    unsigned seq, seq_after;
    do {
        seq = pthread_seqlock_rdlock(&lock);
        int temp_val = val; 
        seq_after = pthread_seqlock_rdunlock(&lock);
        if (seq == seq_after) {
            printf("Read vaule = %d\n", temp_val);
            break;
        }
    } while (1); 
    return NULL;
}

int main()
{
   pthread_t threads[100];
   pthread_seqlock_init(&lock);
   int i;
   for( i = 0;i<100;i++){
   	 	if(i % 2 == 0){
   	 		pthread_create(&threads[i],NULL,writer,NULL);	
		}
		else{
			pthread_create(&threads[i],NULL,reader,NULL);
		}
   }
   for ( i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }

   return 0;
}
