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
    ProcessList(float arrivalLambda, float serviceLambda);
    ProcessList();
    ~ProcessList();
    void listToConsole();
    Process* getProcess();
    bool isEmpty();
    std::list<Process*> processes;
    void populateList(float arrivalLambda, float serviceLambda);
    float genExponentialRandom(float lambda);

};
#endif
