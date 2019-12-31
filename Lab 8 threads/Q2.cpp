#include <iostream>
#include <pthread.h>
#include <string.h>
 #include <stdlib.h>

using namespace std;


void* max(void* para)
{
 int*arr=(int*) para;
 cout<<arr[0]<<endl;
 int x;cin>>x;
 int i=0,max=0;

 while(arr[i]!=-1)
 {
 	if(max<arr[i])
 	max=arr[i];
 	i++;
 }


  return( (void*) max);
}
void* avg(void* para)
{
 int*arr=(int*) para;
  cout<<arr[0]<<endl;int x;cin>>x;
 int i=0,max=0;

 while(arr[i]!=-1)
 {
 	max=max+arr[i];
 	i++;
 }
 
int avg=max/(i+1);


  return( (void*) avg);
}
void* min(void* para)
{
 int*arr=(int*) para;
  cout<<arr[0]<<endl;int x;cin>>x;
 int i=0,min=99999;
 
 while(arr[i]!=-1)
 {
 	if(min>arr[i])
 	min=arr[i];
 	i++;
 }
  
  return( (void*) min);
}
int main(int argc, char*argv[])
{
	pthread_t id[3];
	int*my=new int[argc+1];
	int i=0;
	for(;i<argc-1;i++)
	{
	  my[i]=atoi(argv[i+1]);
	}
	i++;
	cout<<my[0]<<endl<<endl;
	my[i]=-1;
	  if(pthread_create(&id[0], NULL, &max, &my)==-1)
	  {
	      cout<<"Thread Creation Failed!"<<endl;
	      return 1;
	  }
	   if(pthread_create(&id[1], NULL, &avg, &my)==-1)
	  {
	      cout<<"Thread Creation Failed!"<<endl;
	      return 1;
	  }
	   if(pthread_create(&id[2], NULL, &min, &my)==-1)
	  {
	      cout<<"Thread Creation Failed!"<<endl;
	      return 1;
	  }
	  int*max;
	  int*avg;
	  int*min;
	pthread_join(id[0], (void**) &max);
	pthread_join(id[1], (void**) &avg);
	pthread_join(id[2], (void**) &min);
	cout<<"The average value is "<<*avg<<endl;
	cout<<"The minimum value is "<<*min<<endl;
	cout<<"The maximum value is "<<*max<<endl;
}
