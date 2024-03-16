#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "ProcessList.h"
#include "EventQueue.h"
#include "ReadyQueue.h"

using std::string;

extern EventQueue* eq;
extern ReadyQueue* rq;
extern float* clock;
extern int* cpu_status;
extern int* counter;
extern int* sample_queue;
extern int* sample_polls;
extern bool* exit;

int argChecks(int argc, char *argv[]);
void argChecktoConsole(int flag);
void handle_arrival(Event* event, ProcessList* processes);
void handle_departure(Event* event, ProcessList* processes);
void handle_poll(Event* event, ProcessList* processes);
void tick(ProcessList* processes);


#endif