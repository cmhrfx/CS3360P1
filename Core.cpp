#include "Core.h"

Core::Core() {
    float time_piece = 0;       // global clock
    int cpu_status = 0;           // 0 = not busy, 1 = busy
    int sample_queue = 0;         // x += number of processes in rq
    int sample_polls = 0;         // track number of polls
    int arrivals = 0;              
    int departures = 0;
    bool complete = false;
    bool processes_empty = false;
    bool events_empty = false;
    ReadyQueue rq;      // instantiated as empty
    EventQueue eq;      // instantiated with 1 initial departure event
    ProcessList processes;
};