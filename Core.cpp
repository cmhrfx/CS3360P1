#include "Core.h"

Core::Core() {
    time_piece = 0;       // global clock
    cpu_status = 0;           // 0 = not busy, 1 = busy
    sample_queue = 0;         // x += number of processes in rq
    sample_polls = 0;         // track number of polls
    turnarounds = 0;
    cpu_active_count = 0;
    polling_interval = 0.1;
    arrivals = 0;              
    departures = 0;
    complete = false;
    processes_empty = false;
    events_empty = false;
    Process* pollProcess = new Process(-1,0,0);
};