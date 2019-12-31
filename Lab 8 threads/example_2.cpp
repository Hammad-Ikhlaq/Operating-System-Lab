#include <iostream>
using namespace std;
#include <string.h>

struct Student
{
   int rollNumber;
   char name[20];

};

void* myFunc(void* param)
{

   Student *student=(Student*) param;
   
   Student *updatedStudent=new Student;
   strcpy(updatedStudent->name, student->name);
   updatedStudent->rollNumber=10;

  pthread_exit( (void*) updatedStudent);
  // or u can use: return (void*) updatedStudent; 
  //do not use exit routine, it will terminate the whole process

}


int main()
{


  pthread_t id;
  Student std;

  strcpy(std.name, "abc");
  std.rollNumber=1;
 
  if (pthread_create(&id, NULL, &myFunc, &std)==-1)
  {
      cout<<"Thread Creation Failed!"<<endl;
      return 1;
  }
  

  Student *updatedStd;
  pthread_join(id, (void**) &updatedStd);
  cout<<updatedStd->rollNumber;
}
