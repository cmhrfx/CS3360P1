#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "ProcessList.h"
#include "EventQueue.h"
#include "ReadyQueue.h"

using std::string;
using std::cout;
using std::endl;

extern Core core;
extern bool const DEBUG;

int argChecks(int argc, char *argv[]);
void argChecktoConsole(int flag);
void handleArrival(Event* event, ProcessList* processes);
void handleDeparture(Event* event, ProcessList* processes);
void handlePoll(Event* event, ProcessList* processes);


#endif