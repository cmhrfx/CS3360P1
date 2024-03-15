#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "ProcessList.h"
#include "EventQueue.h"
#include "ReadyQueue.h"

extern EventQueue* eq;
extern ReadyQueue* rq;
extern ProcessList* processes;
extern float* clock;
extern int* cpu_status;
extern int* counter;

using std::string;

int argChecks(int argc, char *argv[]);
void argChecktoConsole(int flag);
void handle_arrival(Event* event);
void handle_departure(Event* event);
bool tick(Event* event);


#endif