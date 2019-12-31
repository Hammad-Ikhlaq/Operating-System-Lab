#include<iostream>
#include<unistd.h>
#include<cstring>
#include<fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>
using namespace std;
int main(int argc, char*argv[])
{
	int b[2];
	pipe(b);
	char buf[1000];
	pid_t pid=fork();
	if(pid==0)
	{
		int fd=open(argv[1],O_RDONLY);
		read(fd, buf, 1000);
		write(b[1], buf, strlen(buf));
		close(b[1]);
	}
	if(pid>0)
	{
		read(b[0], buf, 1000);	
		int fd=open(argv[2],O_WRONLY);
		cout<<buf<<endl;
		write(fd, buf, 1000);
			close(b[0]);
	}

return 0;
}
