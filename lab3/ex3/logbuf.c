#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAX_LOG_LENGTH 10
#define MAX_BUFFER_SLOT 6
#define MAX_LOOPS 30
char logbuf[MAX_BUFFER_SLOT][MAX_LOG_LENGTH];

int count; // Index to wirte
void flushlog();
pthread_mutex_t lock;
pthread_cond_t buffer_full;
pthread_cond_t buffer_empty;
struct _args
{
   unsigned int interval;
};

void *wrlog(void *data)
{
   char str[MAX_LOG_LENGTH];
   int id = *(int*) data;
   pthread_mutex_lock(&lock);
   usleep(20);
   sprintf(str, "%d", id);
   while(count>=MAX_BUFFER_SLOT){
   		pthread_cond_wait(&buffer_full, &lock);
   }
   strcpy(logbuf[count], str);
   printf("wrlog(): %d \n", id);
   count++;
   pthread_cond_signal(&buffer_empty);
   pthread_mutex_unlock(&lock);
   return 0;
}

void flushlog()
{
   int i;
   char nullval[MAX_LOG_LENGTH];
   pthread_mutex_lock(&lock); 
   while(count <= 0  ){
   		pthread_cond_wait(&buffer_empty,&lock);
   }
   printf("flushlog()\n");
   sprintf(nullval, "%d", -1);
   for (i = 0; i < count; i++)
   {
      printf("Slot  %i: %s\n", i, logbuf[i]);
      strcpy(logbuf[i], nullval);
   }
   fflush(stdout);
   /*Reset buffer */
   count = 0;
   pthread_cond_broadcast(&buffer_full);
   pthread_mutex_unlock(&lock);
   sleep(5);
   return;

}

void signal_handler(int signum) {
   printf(": %d\n", signum);
   flushlog();
}

void *timer_start(void *args)
{
   while (1)
   {
      flushlog();
      /*Waiting until the next timeout */
      usleep(((struct _args *) args)->interval);
   }
}

int main()
{
   int i;
   count = 0;

   pthread_t tid[MAX_LOOPS];
   pthread_t lgrid;
   int id[MAX_LOOPS];

   struct _args args;
   args.interval = 500e3; // 500 msec ~ 500,000 usec

   // In PID và hu?ng d?n s? d?ng tín hi?u
   printf("Program started with PID: %d\n", getpid());
   printf("To use signals:\n");
   printf("Send SIGUSR1: kill -SIGUSR1 %d\n", getpid());
   printf("Send SIGUSR2: kill -SIGUSR2 %d\n", getpid());

   // Initialize mutex and condition variables
   pthread_mutex_init(&lock, NULL);
   pthread_cond_init(&buffer_full, NULL);
   pthread_cond_init(&buffer_empty, NULL);

   // Register signal handler
   signal(SIGUSR1, signal_handler);
   signal(SIGUSR2, signal_handler);

   // Create thread to periodically call flushlog()
   pthread_create(&lgrid, NULL, timer_start, (void*) &args);

   // Create threads to write logs
   for (i = 0; i < MAX_LOOPS; i++) {
      id[i] = i;
      pthread_create(&tid[i], NULL, wrlog, (void*) &id[i]);
   }

   // Wait for all write threads to finish
   for (i = 0; i < MAX_LOOPS; i++) {
      pthread_join(tid[i], NULL);
   }

   sleep(5); // Allow the flushlog thread to complete

   // Destroy mutex and condition variables
   pthread_mutex_destroy(&lock);
   pthread_cond_destroy(&buffer_full);
   pthread_cond_destroy(&buffer_empty);

   return 0;
}

