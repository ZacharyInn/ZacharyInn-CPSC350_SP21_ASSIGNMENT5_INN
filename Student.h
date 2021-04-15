#include <iostream>
using namespace std;

class Student
{
  public:
    Student();
    Student(int setArrival,int setUse);
    ~Student();
    void addWait();
    int getArrival();
    int getUseTime();
    int getWaitTime();

  private:
    int arrivalTime;
    int useTime;
    int waitTime;
};
