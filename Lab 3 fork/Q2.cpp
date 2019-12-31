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
		int count=argc;
		int sum=0,i=0;
		while(count!=0)
		{
			sum=sum+atoi(argv[i]);
			i++;
			count--;
		 }
		 cout<<"sum="<<sum<<endl;
		 return 0;
	}
	pid=fork();
	if(pid==0)
	{
 		int count=argc;
		int sum=0,i=0;
		while(count!=0)
		{
			sum=sum+atoi(argv[i]);
			i++;
			count--;
		 }
		 sum=sum/(argc-1);
		 cout<<"average="<<sum<<endl;
		  return 0;
	}
	pid=fork();
	if(pid==0)
	{
 		int count=argc;
		int max=atoi(argv[1]),i=0;
		while(count!=0)
		{
			if(atoi(argv[i])>max)
			max=atoi(argv[i]);
			i++;
			count--;
		 }
		 cout<<"max="<<max<<endl;
		  return 0;
	}
	wait(NULL);
	wait(NULL);
	wait(NULL);
return 0;
}
