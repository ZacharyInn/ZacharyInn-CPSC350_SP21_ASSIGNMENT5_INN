#include <iostream>
#include "Registrar.h"
#include <array>

using namespace std;

Registrar::Registrar()
{
  totalWindows;
  numWinOpen = 0;
  totalIdleTime = 0;
  studentHelpTimers = new int[1];
  idleTimes = new int[1];
  meanWinIdle = 0;
  maxWinIdle = 0;
  winOverFive = 0;
}

Registrar::Registrar(int numOpen)
{
  totalWindows = numOpen;
  studentHelpTimers = new int[numOpen];
  for (int i = 0; i < totalWindows; i++)
  {
    studentHelpTimers[i] = -1;
  }
  idleTimes = new int[numOpen];
  numWinOpen = numOpen;
  totalIdleTime = 0;
  meanWinIdle = 0;
  maxWinIdle = 0;
  winOverFive = 0;
}

Registrar::~Registrar()
{

}

bool Registrar::isWindowOpen()
{
  if (numWinOpen > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Registrar::isWindowInUse()
{
  if (numWinOpen != totalWindows)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Registrar::useWindow(int timeNeeded)
{
  numWinOpen--;
  checkMaxIdleTime();
  for (int i = 0; i < totalWindows; i++)
  {
    if (studentHelpTimers[i] < 0)
    {
      studentHelpTimers[i] = timeNeeded;
      totalIdleTime += idleTimes[i];
      idleTimes[i] = 0;
      break;
    }
  }
}

void Registrar::checkOpenWindow()
{
  for (int i = 0; i < totalWindows; i++)
  {
    if ((studentHelpTimers[i] - 1) == 0)
    {
      numWinOpen++;
    }
  }
}

void Registrar::checkMaxIdleTime()
{
  for (int i = 0; i < totalWindows; i++)
  {
    if (idleTimes[i] > maxWinIdle)
    {
      maxWinIdle = idleTimes[i];
    }
  }
  for (int i = 0; i < totalWindows; i++)
  {
    if (idleTimes[i] > 5)
    {
      winOverFive++;
    }
  }

}

void Registrar::clockTick()
{
  for (int i = 0; i < totalWindows; i++)
  {
    if (studentHelpTimers[i] <= 0)
    {
      idleTimes[i] += 1;
    }
  }
  checkOpenWindow();
  for (int i = 0; i < totalWindows; i++)
  {
    studentHelpTimers[i] -= 1;
  }
}

void Registrar::finalCheck()
{
  for (int i = 0; i < totalWindows; i++)
  {
    if (idleTimes[i] > 0)
    {
      totalIdleTime += idleTimes[i];
    }
    if (idleTimes[i] > 5)
    {
      winOverFive++;
    }
    if (idleTimes[i] > maxWinIdle)
    {
      maxWinIdle = idleTimes[i];
    }
  }
  calculateMean();
}

void Registrar::calculateMean()
{
  meanWinIdle = totalIdleTime / totalWindows;
}

void Registrar::printOutput()
{
  cout << "5. Mean window idle time: " << meanWinIdle << endl;
  cout << "6. Longest window idle time: " << maxWinIdle << endl;
  cout << "7. # of windows idle for over 5 mins: " << winOverFive << endl;
}
