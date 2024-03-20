#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Core.h"

using std::string;
using std::cout;
using std::endl;
using std::setw;

extern Core core;   // using a global struct helps keep functions short and clean

int argChecks(int argc, char *argv[]);      // check cmdline args
void argChecktoConsole(int flag);           // output cmdline arg errors
void handleArrival(Event* event);           // logic sequence for arrival events
void handleDeparture(Event* event);         // logic sequence for departure events
void handlePoll(Event* event);              // logic sequence for poll events
void outputMetrics(float arrivalRate, float serviceTime);
                                           // write metrics to console
void logMetrics(float arrivalRate, float serviceTime, string path);

#endif