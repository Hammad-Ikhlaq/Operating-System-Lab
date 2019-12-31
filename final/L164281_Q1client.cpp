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

 int key=shmget(100, 1024, IPC_CREAT | 0666 ); 
 char* ptr= (char*) shmat(key, NULL, 0); 
 
         cout<<"Enter command\n";
        cin.getline(ptr,1024);
 int key2=shmget(1, 4, IPC_CREAT | 0666 ); 
   char * myfifo =new char[20];
   strcpy(myfifo, "clientpipe.txt");
   mkfifo(myfifo, 0666);
 
  int* c= (int*) shmat(key2, NULL, 0); 
  *c=1;
  
   int key3=shmget(2, 1024, IPC_CREAT | 0666 );

 char* last= (char*) shmat(key3, NULL, 0); 

        int fd1 = open(myfifo,O_RDONLY);
       
        read(fd1, ptr, strlen(ptr));
        cout<<ptr<<endl;

 shmdt(ptr);

shmctl(key, IPC_RMID, NULL);

}
