#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
#include <string.h> 

#define TEST_STRING "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\r\n"
#define TEST_STRING2 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

int main() {
   int pipefds[2];
   int returnstatus;
   int pid;
   char readmessage[20];
   returnstatus = pipe(pipefds);
   if (returnstatus == -1) {
	  printf("Unable to create pipe\n");
	  return 1;
   }
   pipefds[1] = open("sampleFile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(pipefds[0]) 
	{ 
		printf("Files open successfully for pipefds[0]\n");
	}
	else 
	{ 
		printf("Error to open file.\n");
	}

	pipefds[0] = open("sampleFile.txt", O_RDONLY, 0);
	if(pipefds[1]) 
	{ 
		printf("Files open successfully for pipefds[1]\n");
	}
	else 
	{ 
		printf("Error to open file for pipefds[1].\n");
	}
	pid = fork();
   // Child process
   if (pid == 0) {
      read(pipefds[0], readmessage, sizeof(readmessage));
      printf("Child Process - Reading from pipe – Message 1 is %s\n", readmessage);
   } else { //Parent process
	  write(pipefds[1], TEST_STRING2, strlen(TEST_STRING2));
   }
   return 0;
}
