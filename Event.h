#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Process.h"

using std::string;

class Event{
public:
    Event(Process* process, float time, std::string type);
    Event();
    
    Process* process;
    float time;
    string type;
};



#endif