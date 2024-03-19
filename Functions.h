#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "Core.h"

using std::string;
using std::cout;
using std::endl;

extern Core core;
extern bool const DEBUG;

int argChecks(int argc, char *argv[]);
void argChecktoConsole(int flag);
void handleArrival(Event* event);
void handleDeparture(Event* event);
void handlePoll(Event* event);
void schedulePoll();


#endif