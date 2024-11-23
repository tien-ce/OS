#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int get_input(char* fileName, int arr_rating[]) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("ERROR with opening file\n");
        return -1;
    }

    int userID, movieID, rating, timeStamp;
    int i = 0;
    while (fscanf(file, "%d %d %d %d", &userID, &movieID, &rating, &timeStamp) != EOF) {
        arr_rating[i] = rating;
        i++;
    }
    fclose(file);
    return i;
}

int main() {
	key_t key = 0X12;
	int shmid;
	shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);
	double *shared_array = (double*) shmat(shmid, NULL, 0);
    int id1 = fork();
    int id2 = fork();	
    char fileName[100];
    int size;
    int arr_rating[60000];

    if (id1 == 0) { // Tien trinh con thu nhat
        strcpy(fileName, "movie-100k_1.txt"); 
        size = get_input(fileName, arr_rating);
        int i;
        double sum = 0;
        for(i =0;i<size;i++){
        	sum+= arr_rating[i];
		}
		shared_array[0] = sum / size;
		return 0; 
    } else { 
       if(id2==0){ // Tien trinh con thu 2
        strcpy(fileName, "movie-100k_2.txt"); 
        size = get_input(fileName, arr_rating);
        int i;
        double sum = 0;
        for(i =0;i<size;i++){
        	sum+= arr_rating[i];
		}
		shared_array[1] = sum / size;
		return 0;
       }
       else{ // Tien trinh cha
       	wait(NULL);
       	wait(NULL);
	   }
	printf("AVG from child process1 is %.2f\n",shared_array[0]);
	printf("AVG from child process2 is %.2f\n",shared_array[1]);
    }
	shmctl(shmid, IPC_RMID, NULL);   
    return 0;
}
