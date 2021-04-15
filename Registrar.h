
#include <iostream>
using namespace std;

class Registrar
{
  public:
    Registrar();
    Registrar(int numOpen);
    ~Registrar();
    bool isWindowOpen();
    bool isWindowInUse();
    void useWindow(int timeNeeded);//numWinOpen--;put timer on next open window;
    void checkOpenWindow();//check if any timers are 0, if timer is 0 numWinOpen++;
    void checkMaxIdleTime(); //if idleTimes[i] > maxWinIdle set maxWinIdle, if idleTimes[i] > 5 winOverFive++;
    void clockTick(); //add to idleTimes[i] if timers[i] is 0, ,checkMax(), subtract 1 from timers, checkOpenWindow()
    void calculateMean(); //do calculation
    void finalCheck();
    void printOutput();//print out output variables

  private:
    //Registrar Window
    int totalWindows;
    int numWinOpen;
    float totalIdleTime;
    int* studentHelpTimers;
    int* idleTimes;

    //output variables
    float meanWinIdle;
    int maxWinIdle;
    int winOverFive;
};
