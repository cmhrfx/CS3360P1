#include "Core.h"

Core::Core() {
    time_piece = 0;
    cpu_status = 0;
    sample_queue = 0;
    sample_polls = 0;
    turnarounds = 0;            
    cpu_active_count = 0;
    polling_interval = 0.1;
    arrivals = 0;              
    departures = 0;
    processes_empty = false;
    events_empty = false;
    pollProcess = new Process(-1,0,0);
};