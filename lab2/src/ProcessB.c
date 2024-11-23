
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#define MAX_TEXT 100
#define PERMS 0644
#define MSG_KEY 0x124
#define MSG_KEY1 0x125
struct my_msgbuf {
   long mtype;
   char mtext[MAX_TEXT];
};


void *sender(void *arg){
   struct my_msgbuf buf;
   int len;
   int msqid; // ID MessageQueue
   key_t key;
   key = MSG_KEY;
   if ((msqid = msgget(key,  MSG_KEY | IPC_CREAT)) == -1) {
        perror("ERROR When creat Message Queue");
        exit(1);
   }

   printf("Message send conection with ID: %d\n", msqid);
   buf.mtype = 1; 

   while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
      len = strlen(buf.mtext);
      /* remove newline at end, if it exists */
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
      if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
      perror("msgsnd");
   }
   strcpy(buf.mtext, "end");
   len = strlen(buf.mtext);
   if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
   perror("msgsnd");
   
   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
}

void  *receiver(void *arg){
   struct my_msgbuf buf;
   int toend;
   int msqid; // ID MessageQueue 
   key_t key;
   key = MSG_KEY1;
   if ((msqid = msgget(key,  MSG_KEY | IPC_CREAT)) == -1) {
        perror("ERROR When creat Message Queue");
        exit(1);
   }

   printf("Message recive conection with ID: %d\n", msqid);
   
   for(;;) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      printf("recvd: \"%s\"\n", buf.mtext);
      toend = strcmp(buf.mtext,"end");
      if (toend == 0)
      break;
   }
   
   if(msgctl(msqid, IPC_RMID, NULL)==-1){
      exit(1);
   }
   printf("message queue: done receiving messages.\n");
   pthread_exit(NULL);
}


int main() {
    pthread_t send_thread, recv_thread;

    if (pthread_create(&send_thread, NULL, sender, NULL) != 0) {
        perror("ERROR When create thread");
        exit(1);
    }

    if (pthread_create(&recv_thread, NULL, receiver, NULL) != 0) {
        perror("ERROR When create thread");
        exit(1);
    }


    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);
	
    printf("End Message Queue\n");
    return 0;
}

