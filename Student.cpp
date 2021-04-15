#include <iostream>
#include "Student.h"
using namespace std;

Student::Student()
{
  arrivalTime = 0;
  useTime = 0;
  waitTime = 0;
}

Student::Student(int setArrival, int setUse)
{
  arrivalTime = setArrival;
  useTime = setUse;
  waitTime = 0;
}

Student::~Student()
{

}

void Student::addWait()
{
  waitTime++;
}

int Student::getArrival()
{
  return arrivalTime;
}

int Student::getUseTime()
{
  return useTime;
}

int Student::getWaitTime()
{
  return waitTime;
}
