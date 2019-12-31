#include <iostream>
#include <fstream>
using namespace std;

void main(int argc, char * arg[])
{
	char var[100];
	ifstream fin;
	fin.open(arg[1]);
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin>>var;
			cout<<var;
		}
	}
	else
	cout<<"error!"<<endl;
	return 0;
}
