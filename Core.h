#ifndef CORE_H
#define CORE_H

#include "ReadyQueue.h"
#include "EventQueue.h"
#include "ProcessList.h"
#include <list>

struct Core
{
    // properties
    float time_piece;          // global clock
    int cpu_status;            // 0 = not busy, 1 = busy
    float sample_queue;          // x += number of processes in rq
    float sample_polls;          // track number of polls
    float turnarounds;
    float cpu_active_count;
    float polling_interval;
    int arrivals;              
    int departures;
    int poll_period;
    bool complete;
    bool processes_empty;
    bool events_empty;
    ProcessList processes;      // inserted after construction
    ReadyQueue rq;      // instantiated as empty
    EventQueue eq;      // instantiated with 1 initial departure event  
    Process* pollProcess;

    // methods
    Core();

};




#endif