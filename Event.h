#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Process.h"

using std::string;

// For ease with switch, using integers for type
// 0 = departure, 1 = arrival
class Event{
public:
    Event(Process* process, float time, std::string type);
    Event();
    Process* getEventProcess();
    float getEventTime() const;
    string getEventType() const;

    int getEventProcessId() const;
    float getEventProcessAT() const;
    float getEventProcessST() const;
    
    Process* process;
    float time;
    string type;
};



#endif