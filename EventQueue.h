#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Event.h"
#include "ProcessList.h"
#include "Process.h"
#include <list>

class EventQueue {
public:
    EventQueue();
    ~EventQueue();
    Event* getEvent();
    void scheduleEvent(Event* event);
    

private:
    std::list<Event*> events;
};


#endif