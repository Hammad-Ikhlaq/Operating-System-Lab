#include<iostream>
#include <fcntl.h>
#include<sys/wait.h>
using namespace std;
int main(int argc, char*argv[])
{
	int i=0;
	pid_t pid=fork();
	if(pid==0)
	{
		int b[2];
		int fd=open(argv[1],O_RDONLY);
		read(fd, buf, 1000);
		write(b[1], buf, strlen(buf));
	}
	if(pid>0)
	{
		wait(NULL);
		while(i<strlen(buf))
		{
				if(buf[i]>96&&buf[i]<126)
				{
					buf[i]=buf[i]-32;
				}
				else if(buf[i]>65&&buf[i]<90)
				{
					string[i]=string[i]+32;
				}
				else if((buf[i]>60&&buf[i]<67)||(buf[i]>=70&&buf[i]<=71))
				{
					buf[i]=" ";
				}
				i++;	
			
		}	
		
	
	
		read(b[0], buf, 1000);	
		int fd=open(argv[2],O_WRONLY);
		cout<<buf<<endl;
		write(fd, buf, 1000);
			close(b[0]);
	}

}
