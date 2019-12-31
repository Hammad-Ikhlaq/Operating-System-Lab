#include <iostream>
#include <sys/shm.h>
#include <stdio.h>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;


int main()
{

 int key=shmget(100, 1024, 0);

 char* ptr= (char*) shmat(key, NULL, 0); 
 
 int key2=shmget(1, 4, 0);
   int* c= (int*) shmat(key2, NULL, 0); 
   *c=0;
   
   char * myfifo =new char[20];
   strcpy(myfifo, "clientpipe.txt");
   mkfifo(myfifo, 0666);
   
   while(*c==0)cout<<"busy waiting\n";
 
 int key3=shmget(2, 1024, 0);

 char* last= (char*) shmat(key3, NULL, 0); 
  int fd = open(last,O_WRONLY);
    dup2(fd,1);
 
  execlp(ptr, ptr ,NULL);
  write(fd, ptr, strlen(ptr));

 shmdt(ptr);

 
}
