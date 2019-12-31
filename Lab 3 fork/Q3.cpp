#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
using namespace std;
int main(int argc, char*argv[])
{
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		cout<<"\n\n\n\n\n";
		execlp("ping" ,"ping","google.com",NULL);
		 return 0;
	}
	pid=fork();
	if(pid==0)
	{
			cout<<"\n\n\n\n\n";
 			execlp("mkdir" ,"mkdir","./Hammad",NULL);
		  return 0;
	}
	pid=fork();
	if(pid==0)
	{
		cout<<"\n\n\n\n\n";
 		execlp("ls" ,"ls","-l",NULL);
		 return 0;
	}
	pid=fork();
	if(pid==0)
	{
		cout<<"\n\n\n\n\n";
 		execlp("cp" ,"cp","/home/oracle/huz/main.cpp","/home/oracle",NULL);
		 return 0;
	}
	wait(NULL);
	wait(NULL);
	wait(NULL);
	wait(NULL);
return 0;
}
