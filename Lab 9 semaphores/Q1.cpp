#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <pthread.h>
#include <sys/shm.h>
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;
char a;
sem_t sem1;
sem_t sem2;
char array[20];

struct ob
{
	char filename[20];
};

void*Producer(void *para)
{

	ob*object=(ob*)para;
 	ifstream fin(object->filename);
	int i=0;
	while(1)
	{
		sem_wait(&sem1);
		for(;i<20;i++)
		fin>>array[i];
		sem_post(&sem2);
		i=0;
		if(fin.eof())
		{
		i++;
		array[i]='$';
		return 0;
		}
	}

return 0;
	
}

void*Consumer(void *)
{  
   while (true)
    {
      sem_wait(&sem2);
        for(int i=0;i<20;i++)
	{
		if(array[i]=='$')
		return 0;
		cout<<array[i];
	}
	cout<<endl;
	cin.get();
      sem_post(&sem1);
    }

}

int main(int argc, char*argv[])
{
	ob object;
	strcpy(object.filename,argv[1]);
	
	pthread_t id1, id2;
	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);
  
  pthread_create(&id1, NULL, &Producer, &object);
  pthread_create(&id2, NULL, &Consumer, &object);
  
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
return 0;
}
