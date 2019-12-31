#include<iostream>
#include<unistd.h>
using namespace std;
int main(int argc, char*argv[])
{
	pid_t pid;
	pid=fork();
	int x=100;
	if(pid==0)
	{
	while(x!=0)
	{
	cout<<x<<" I am a child\n";
	x=x--;
	}
	}
	if(pid>0)
	{
	while(x!=0)
	{
	cout<<x<<" I am a parent\n";
	x=x--;
	}
	}
return 0;
}
