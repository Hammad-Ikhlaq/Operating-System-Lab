#include <iostream>
#include <string.h>
#include<semaphore.h>
using namespace std;
int carsE[40] = 0;
int countE = 40;
int carsW[40] = 0;
int countW = 40;
int carsN[40] = 0;
int countN = 40;
int carsS[40] = 0;
int countS = 40;
void* East(void* param)
{
 while (true)
 {
  sem_wait(&fromEast);
  countE--;
  
  sem_wait(&B3);
  
  sem_post(&B3);
  
  sem_wait(&B2);
  
  sem_post(&B2);
  
  sem_wait(&B1);
  
  sem_post(&B1);
  
  sem_post(&fromWest);
 }

  pthread_exit(NULL);
  //do not use exit routine, it will terminate the whole process


}


void* West(void* param)
{
 while (true)
 {
  sem_wait(&fromWest);
  countW--;
  sem_wait(&B1);
  
  sem_post(&B1);
  
  sem_wait(&B2);
  
  sem_post(&B2);
  
  sem_wait(&B3);
  
  sem_post(&B3);
  
  sem_post(&fromEast);
 }

  pthread_exit(NULL);
  //do not use exit routine, it will terminate the whole process


}

void* North(void* param)
{

 while (true)
 {
  sem_wait(&fromNorth);
  countN--;
  
  sem_wait(&A2);
  
  sem_post(&A2);
  
  sem_wait(&B2);
  
  sem_post(&B2);
  
  sem_wait(&C2);
  
  sem_post(&C2);
  
  sem_post(&fromSouth);
 }
  pthread_exit(NULL);
  //do not use exit routine, it will terminate the whole process


}


void* South(void* param)
{

 while (true)
 {
  sem_wait(&fromSouth);
  countS--;
  sem_wait(&C2);
  
  sem_post(&C2);
  
  sem_wait(&B2);
  
  sem_post(&B2);
  
  sem_wait(&A2);
  
  sem_post(&A2);
  
  sem_post(&fromNorth);
 }
  pthread_exit(NULL);
  //do not use exit routine, it will terminate the whole process


}

char a;

sem_t A2;
sem_t B2;
sem_t C2;
sem_t B1;
sem_t B3;

sem_t fromNorth;
sem_t fromWest;
sem_t fromEast;
sem_t fromSouth;

int main()
{


  pthread_t id;
  int var=100;


  sem_init(&A2, 0, 1);
  sem_init(&B2, 0, 1);
  
  sem_init(&C2, 0, 1);
  sem_init(&B1, 0, 1);
  
  sem_init(&B3, 0, 1);
  
  sem_init(&fromNorth, 0, 1);
  sem_init(&fromEast, 0, 1);
  
  sem_init(&fromSouth, 0, 0); // opposite to north
  sem_init(&fromWest, 0, 0); // opposite to east
  
  if (pthread_create(&id, NULL, &East, NULL)==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }
  
    if (pthread_create(&id, NULL, &West, NULL)==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }
  
    if (pthread_create(&id, NULL, &North, NULL)==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }
  
    if (pthread_create(&id, NULL, &South, NULL)==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }
  


  pthread_join(id, NULL);
  
 return 0;
}

