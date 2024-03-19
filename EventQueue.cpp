#include "EventQueue.h"

EventQueue::EventQueue()
{
    Process* initiationProcess = new Process(0,0,0);
    Event* initiationEvent = new Event(initiationProcess,0,"arrival");
    events.push_back(initiationEvent);
};

void EventQueue::scheduleEvent(Event* newEvent, Event* oldEvent)
{
    if (newEvent->getEventTime() >= oldEvent->getEventTime())
    {
        events.push_back(newEvent);
    }
    else
    {
        events.push_front(newEvent);
    }
    
}

// overloaded function for events that need to go next. Namely: pulled from RQ and poll events. 
void EventQueue::scheduleEvent(Event* newEvent)
{
    events.push_front(newEvent);
}

Event* EventQueue::getEvent()
{
    Event* event = nullptr;
    if (!events.empty())
    {
        event = events.front();
        events.pop_front();
    }
    return event;
}

EventQueue::~EventQueue()
{
    for (auto& event : events)
    {
        delete event;
    }
}