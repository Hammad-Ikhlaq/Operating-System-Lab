#include<iostream>
#include<unistd.h>
#include<cstring>
using namespace std;
int main(int argc, char*argv[])
{
	int a[2],b[2];
	pipe(a);
	pipe(b);
	char string[50];
	cin.getline(string,50);
	pid_t pid=fork();
		if(pid==0)
		{
			char buf[50];
			read(a[0], buf, 50);
			close(a[0]);
			
			int i=0;
			while(i!=(strlen(string)-1))
			{
				if(string[i]>96&&string[i]<126)
				{
					string[i]=string[i]-32;
				}
				else if(string[i]>65&&string[i]<90)
				{
					string[i]=string[i]+32;
				}
				i++;
			}
			write(b[1], string, strlen(string));
			close(b[1]);
		}
		else if(pid>0)
		{
			write(a[1], string, strlen(string));
			char buf[50];
			read(b[0], buf, 50);
			cout<<endl<<buf;
			close(b[0]);
		}

return 0;
}
