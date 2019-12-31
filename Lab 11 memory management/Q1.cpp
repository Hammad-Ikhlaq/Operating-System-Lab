#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/stat.h>
#include <string.h>
using namespace std;
int count=0;
struct box
{
	int start;
	int end;
	char*sub;
	char*data;
};
sem_t sem;

void*f(void *para)
{
	box*my=(box*)para;
	for(int i=my->start; i<my->end-strlen(my->sub);i++)
	{
		if(my->sub[0]==my->data[i])
		{
			bool found=true;
			for(int j=1; j<strlen(my->sub)-1;j++)
			{
				if(my->sub[j]!=my->data[i+j])
				{
					found=false;
				}
			}
			if(found==true)
			{
				sem_wait(&sem);
				count++;
				sem_post(&sem);
			}
		}
	}
}

int main(int argc, char*argv[])
{
	struct stat sb;
	box my1,my2;
	pthread_t id1, id2;
 	sem_init(&sem, 0, 1);
	
	int fd=open(argv[1], O_RDONLY);
	fstat(fd, &sb);
	
	my1.sub=new char[sizeof(argv[2])];
	my2.sub=new char[sizeof(argv[2])];
	strcpy(my1.sub,argv[2]);
	strcpy(my2.sub,argv[2]);
	my1.data=(char*)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	my2.data=(char*)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	my1.start=0;
	my1.end= sb.st_size/2;
	my2.end= sb.st_size;
 	my2.start=sb.st_size/2;
  pthread_create(&id1, NULL, &f, &my1);  	
  pthread_create(&id2, NULL, &f, &my2);
  pthread_join(id1, NULL); 
  pthread_join(id2, NULL);
  cout<<count<<endl;

}
