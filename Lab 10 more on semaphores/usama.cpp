#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <sys/shm.h>
using namespace std;

sem_t  sem1;
sem_t  sem2;

int main(int argc ,char* argv[])
{
sem_init (&sem1 , 1 ,1);
sem_init (&sem2 , 1 ,1);

int id1 = shmget(990 , 1024 , 0666 | IPC_CREAT );
int * ptr= (int*)shmat(id1, NULL , 0);

int pid1=fork();
if(pid1==0)
{
	int sum=0;
	int number=0;
	int index=-1;
	ifstream fin;
	fin.open("file1.txt");
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			sum = sum + number;
			fin >> number;
			index ++;
		}
		sem_wait(&sem1);
		ptr[0]=sum;
		ptr[1]=index;
		sem_wait(&sem2);
		cout<<"SUM1 = "<<sum<<endl;
		
	}
	return 0;
}

int pid2=fork();
if(pid2==0)
{
	int sum=0;
	int number=0;
	int index=-1;
	ifstream fin;
	fin.open("file2.txt");
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			sum = sum + number;
			fin >> number;
			index ++;
		}
		sem_wait(&sem1);
		ptr[0]=sum;
		ptr[1]=index;
		sem_wait(&sem2);
		cout<<"SUM2 = "<<sum<<endl;
	}
	return 0;
}


int sum1=0;
sum1=ptr[0];
int size1=0;
size1=ptr[1];

sem_post(&sem1);


int sum2=0;
sum2=ptr[0];
int size2=0;
size2=ptr[1];
sem_post(&sem1);

int total=sum1+sum2;
cout<<"Total = "<<total<<endl;

int Average=total/(size1+size2);
cout<<"Average = "<<Average<<endl;

ptr[0]=Average;

sem_post(&sem2);
sem_post(&sem2);

wait(NULL);
wait(NULL);

return 0;
}
