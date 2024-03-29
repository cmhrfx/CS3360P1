#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include "Process.h"
#include "Event.h"
#include <ctime>
#include <random>
#include <math.h>
#include <cstdlib>
#include <list>
#include <iostream>
#include <iomanip>

extern const int LENGTH;

class ProcessList{
public:
    std::list<Process*> processes;
    
    ProcessList(float arrivalRate, float serviceTime);
    ProcessList();
    void listToConsole();
    Process* popProcess();
    bool isEmpty();
    void populateList(float arrivalRate, float serviceTime);
    float genExponentialRandom(float lambda);
    ~ProcessList();

    
};
#endif
