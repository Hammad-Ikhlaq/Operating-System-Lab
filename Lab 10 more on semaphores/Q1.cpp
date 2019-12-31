#include <iostream>
#include <semaphore.h>
#include <sys/shm.h>
#include <queue>
#include <string.h>
#include<fstream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

struct box
{
	int count;
	int sum;
};

int main()
{
	int s1 = shmget(1111,16,IPC_CREAT | 0666);
	int s = shmget(3333,8,IPC_CREAT | 0666);//for box
	int x = shmget(2222,8,IPC_CREAT | 0666);//for box
	
	int last1 = shmget(1111,16,IPC_CREAT | 0666);
	int last2 = shmget(1111,16,IPC_CREAT | 0666);
	float average = shmget(3333,8,IPC_CREAT | 0666);
	sem_t*sem1=(sem_t *) shmat(s1,NULL,0);
	sem_t*l1=(sem_t *) shmat(last1,NULL,0);
	sem_t*l2=(sem_t *) shmat(last2,NULL,0);
	float*avg=(float *) shmat(average,NULL,0);
	sem_init(sem1, 0, 1);
	sem_init(l1, 0, 0);
	sem_init(l2, 0, 0);
	box*mybox=(box*) shmat(s,NULL,0);
	box*mybox2=(box*) shmat(x,NULL,0);
	pid_t pid=fork();
	if(pid==0)
	{

		ifstream fin1("in1.txt");
		
		sem_wait(sem1);
		mybox->sum=0;
		mybox->count=0;
		int num;
		fin1>>num;
		while(!fin1.eof())
		{
			
			mybox->sum=mybox->sum+num;
			mybox->count++;
			fin1>>num;
		}
		sem_post(sem1);
		sem_wait(l2);
		cout<<*avg<<endl;
		return 0;
	}
	else if(pid>0)
	{
		pid_t pid=fork();
		if(pid==0)
		{
			ifstream fin2("in2.txt");
		
			sem_wait(sem1);
			mybox2->sum=0;
			mybox2->count=0;
			int num ;
				fin2>>num;
			while(!fin2.eof())
			{
				
				mybox2->sum=mybox2->sum+num;
				mybox2->count++;
				fin2>>num;
			}
			sem_post(sem1);
			sem_wait(l1);
			cout<<*avg<<endl;
			sem_post(l2);
			return 0;
		}
		else if(pid>0)
		{
			float grandsum=mybox->sum;
			float grandcount=mybox->count;
			grandsum=grandsum+mybox2->sum;
			grandcount= grandcount+mybox2->count;
			*avg= grandsum/grandcount;
			sem_post(l1);
		}
	}

}
