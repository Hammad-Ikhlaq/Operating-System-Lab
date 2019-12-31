#include<iostream>
#include<cstdlib>
using namespace std;
void main(int argc, char* arg[])
{
	for(int i = 1 ; i < argc ; i++)
	{
		int a = atoi(arg[i]);
	
		for(int j=i+1 ; j < argc ; j++)
		{
			int b = atoi(arg[j]);
			if(a > b)
			{
				swap(arg[i], arg[j]);
			}
		}
	}
	for(int i=1 ; i < argc ; i++)
	{
		cout<<argv[i]<<"\t";
	}
}
