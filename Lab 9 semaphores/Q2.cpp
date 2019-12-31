#include <iostream>
#include <fstream>
using namespace std;
#include <semaphore.h>
#include <pthread.h>
#include <sys/shm.h>
#include <string>
#include <stdio.h>
#include <cstring>

sem_t sem1;
sem_t sem2;
sem_t sem3;

void*T1(void *)
{
	while(1)
	{
	sem_wait(&sem1);
	cout<<"a";
	cout<<endl;
	sem_post(&sem3);
	}

}

void*T2(void *)
{  int flag=1;
   while(1)
   {
	sem_wait(&sem2);
   	cout<<"b";
	flag++;
	if(flag==3)
	{
	sem_post(&sem1);
	flag=0;
	}
   }
}
void*T3(void *)
{  
   while(1)
   {
   sem_wait(&sem3);
   cout<<"c";
   sem_post(&sem2);
	sem_post(&sem2);
	sem_post(&sem2);
   }

}
int main(int argc, char*argv[])
{
	pthread_t id1, id2,id3;
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 1);
  
  pthread_create(&id1, NULL, &T1, NULL);
  pthread_create(&id2, NULL, &T2, NULL);
  pthread_create(&id2, NULL, &T3, NULL);
  
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
  pthread_join(id3, NULL);
}
