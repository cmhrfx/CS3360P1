#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "ProcessList.h"
#include "EventQueue.h"
#include "ReadyQueue.h"

using std::string;

int argChecks(int argc, char *argv[]);
void argChecktoConsole(int flag);
void handleArrival(EventQueue* eq, ReadyQueue* rq, Event* event, float* clock, int cpu_status);
void handleDeparture(EventQueue* eq, ReadyQueue* rq, Event* event, float* clock, int cpu_status);
bool tick(EventQueue* eq, ReadyQueue* rq, Event* event, int counter, float* clock, int cpu_status);


#endif