#include <iostream>
#include <pthread.h>
#include <string.h>
 #include <stdlib.h>

using namespace std;


void* fibgen(void* para)
{
 int* val=(int*) para;
 int*arr=new int[100]; 
 arr[0]=0,arr[1]=1;
 int c=0,i=0;
 while(c<=val)
 {
 	arr[i+2]=arr[i]+arr[i+1];
 	c=arr[i+2];
 	i++;
 }
 i++;
 arr[i+2]=arr[i]+arr[i+1];
 	c=arr[i+2];
 	i++;
 arr[i]=-1;

  pthread_exit( (void*) arr);
}


int main(int argc, char*argv[])
{
	pthread_t id[argc-1];
	int*my=new int[argc];
	for(int i=0;i<argc-1;i++)
	{
		my[i]=atoi(argv[i+1]);
	  if(pthread_create(&id[i], NULL, &fibgen, &my[i])==-1)
	  {
	      cout<<"Thread Creation Failed!"<<endl;
	      return 1;
	  }
	}
	
	
	for(int i=0;i<argc-1;i++)
	{
		int*ptr;
		 pthread_join(id[i], (void**) &ptr);
		int j=0;
		cout<<"thread "<<i+1<<": "; 
		 while(ptr[j]!=-1)
		 {
		 	cout<<ptr[j]<<" ";
		 	j++;
		 }
		 cout<<"\n";
	}
}
