#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Queue.h"
#include "Registrar.h"
#include "Student.h"

using namespace std;

int main(int argc, char* argv[])
{
  Queue<Student*>* input = new Queue<Student*>();
  Queue<Student*>* waitlist = new Queue<Student*>();

  ifstream inputStream;
  string inputFile = argv[1];
  cout << "Opening " << inputFile << "." << endl;
  inputStream.open(inputFile);
  if (!inputStream.is_open())
  {
    cout << "Could not open " << inputFile << "." << endl;
    return 0;
  }
  int fileNum = 0;
  int arrival = 0;
  int totalStudents = 0;
  inputStream >> fileNum;
  Registrar* windows = new Registrar(fileNum);
  int timeCheck = 1;
  while (!inputStream.eof())
  {
    inputStream >> fileNum;
    if (fileNum < timeCheck)
    {
      cout << "Input error. Please enter correct format." << endl;
      return 0;
    }
    timeCheck = fileNum;
    arrival = fileNum;
    inputStream >> fileNum;
    for (int i = 0; i < fileNum; i++)
    {
      int timeAtWindow = 0;
      inputStream >> timeAtWindow;
      if (fileNum <= 0)
      {
        cout << "Student use time cannot be 0." << endl;
        return 0;
      }
      Student* temp = new Student(arrival,timeAtWindow);
      totalStudents++;
      input->enqueue(temp);
    }
  }

  if (totalStudents == 0)
  {
    cout << "No students entered." << endl;
    return 0;
  }

  int* allWaitTimes = new int[totalStudents];
  int medidx = 0;

  int clock = 0;
  int totalStudentWait = 0;
  int maxStudentWaitTime = 0;
  int waitOverTen = 0;
  Student* currentStudent = input->dequeue();
  bool next = false;
  while(!input->isEmpty() || !waitlist->isEmpty() || windows->isWindowInUse())
  {
    if (currentStudent->getArrival() == -1)
    {
      if (waitlist->isEmpty() && !windows->isWindowInUse())
      {
        break;
      }
    }
    if(clock == currentStudent->getArrival())
    {
      waitlist->enqueue(currentStudent);
      next = true;
    }
    else
    {
      Queue<Student*>* temp = new Queue<Student*>();
      while (!waitlist->isEmpty())
      {
        Student* tempStudent = waitlist->dequeue();
        tempStudent->addWait();
        temp->enqueue(tempStudent);
      }
      while (!temp->isEmpty())
      {
        waitlist->enqueue(temp->dequeue());
      }
      windows->clockTick();
      clock++;
    }
    if(windows->isWindowOpen())
    {
      if(!waitlist->isEmpty())
      {
        Student* temp = waitlist->dequeue();
        int waitTime = temp->getWaitTime();
        allWaitTimes[medidx] = waitTime;
        medidx++;
        if (waitTime > 10)
        {
          waitOverTen++;
        }
        if(waitTime > maxStudentWaitTime)
        {
          maxStudentWaitTime = waitTime;
        }
        totalStudentWait += waitTime;
        windows->useWindow(temp->getUseTime());
      }
    }
    if(!input->isEmpty() && next)
    {
      currentStudent = input->dequeue();
      next = false;
    }
    else if (input->isEmpty() && next)
    {
      currentStudent = new Student(-1,0);
    }
  }
  float meanWait = totalStudentWait / totalStudents;
  int medianWait = 0;
  if (totalStudents % 2 == 0)
  {
    medianWait = allWaitTimes[totalStudents/2] + allWaitTimes[totalStudents/2 + 1] / 2;
  }
  else
  {
    medianWait = allWaitTimes[totalStudents/2];
  }
  cout << "1. Mean student wait time: " << meanWait << endl;
  cout << "2. Median student wait time: " << medianWait << endl;
  cout << "3. Longest student wait time: " << maxStudentWaitTime << endl;
  cout << "4. # of students waiting over 10 minutes: " << waitOverTen << endl;
  windows->finalCheck();
  windows->printOutput();
  inputStream.close();
  return 0;


}
