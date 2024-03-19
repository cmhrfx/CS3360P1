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

class ProcessList{
public:
    ProcessList(float arrivalLambda, float serviceLambda);
    ProcessList();
    ~ProcessList();
    void listToConsole();
    Process* getProcess();

private:
    std::list<Process*> processes;
    void populateList(float arrivalLambda, float serviceLambda);
    float genExponentialRandom(float lambda);

};
#endif
