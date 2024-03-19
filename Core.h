#ifndef CORE_H
#define CORE_H

#include "ReadyQueue.h"
#include "EventQueue.h"
#include "ProcessList.h"

struct Core
{
    // properties
    float* time_piece;          // global clock
    int* cpu_status;            // 0 = not busy, 1 = busy
    int* sample_queue;          // x += number of processes in rq
    int* sample_polls;          // track number of polls
    int* counter;               // counter to tick through processes
    ProcessList processes;      // inserted after construction
    ReadyQueue* rq;      // instantiated as empty
    EventQueue* eq;      // instantiated with 1 initial departure event  

    // methods
    Core();
    void setProcessList(ProcessList* processes);

};




#endif