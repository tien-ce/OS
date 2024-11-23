#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHARE_MEM_SIZE 1024

int main(){
	char* share_mem = mmap(NULL,SHARE_MEM_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANONYMOUS,-1,0);
	if(share_mem == MAP_FAILED ){
		printf("ERROR When creat mmap\n");
		exit(1);
	}
	pid_t pid = fork();
	
	if(pid< 0){
		printf("ERROR When creat child process\n");
		exit(1);
	}
	else if(pid == 0){
		sleep(1); // wait for parent process wirte data
		printf("Child process read from mmap: %s\n",share_mem);
		munmap(share_mem,SHARE_MEM_SIZE);
	}
	else{
		strcpy(share_mem,"Hello from parent process\n");
		wait(NULL);
		munmap(share_mem,SHARE_MEM_SIZE);		
	}
	return 0;
}
