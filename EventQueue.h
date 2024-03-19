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
    void scheduleEvent(Event* newEvent, Event* oldEvent);
    void scheduleEvent(Event* newEvent);

private:
    std::list<Event*> events;
};


#endif