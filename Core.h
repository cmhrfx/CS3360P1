#ifndef CORE_H
#define CORE_H

#include "ReadyQueue.h"
#include "EventQueue.h"
#include "ProcessList.h"
#include <list>

struct Core
{
    // properties
    float time_piece;               // global clock
    float sample_queue;             // x += number of processes in rq
    float sample_polls;             // track number of polls taken
    float turnarounds;              // each departure calculates ind. t time
                                    // then adds it to global var. Later avgd.
    float cpu_active_count;         // number of times cpu busy on poll
    float polling_interval;         // frequency of polling events
    int cpu_status;                 // 0 = not busy, 1 = busy
    int arrivals;                   // number of arrival events
    int departures;                 // number of departure events
    bool processes_empty;           // if processList is empty
    bool events_empty;              // if eventQueue is empty
    ProcessList processes;          // inserted after construction
    ReadyQueue rq;                  // instantiated as empty
    EventQueue eq;                  // instantiated with 2 initial events  
    Process* pollProcess;           // dummy process for polling events

    // methods
    Core();

};




#endif