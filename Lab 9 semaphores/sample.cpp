#include <iostream>
using namespace std;
#include <semaphore.h>
#include <pthread.h>
char a;
sem_t sem1;
sem_t sem2;

void *Writer(void *)
{
 while (true)
 {
  sem_wait(&sem1);
  cin>>a;
  sem_post(&sem2);
 }

}

void* Reader (void *)
{  
   while (true)
    {
      sem_wait(&sem2);
        cout<<"Data Read: "<<a<<endl;
      sem_post(&sem1);
    }

}

int main()
{

   pthread_t id1, id2;
  sem_init(&sem1, 0, 1);
  sem_init(&sem2, 0, 0);
  
  pthread_create(&id1, NULL, &Writer, NULL);
  pthread_create(&id2, NULL, &Reader, NULL);
  
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

}
