#include "EventQueue.h"

EventQueue::EventQueue()
{
    Process* initiationProcess = new Process(0,0,0);
    Event* initiationEvent = new Event(initiationProcess,0,"arrival");
    events.push_back(initiationEvent);
};

void EventQueue::scheduleEvent(Event* event)
{
    if (event->getEventTime() >= getNextEventTime())
    {
        events.push_back(event);
    }
    else
    {
        events.push_front(event);
    }
    
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

float EventQueue::getNextEventTime()
{
    if (!events.empty())
    {
        Event event = *events.front();
        return event.getEventTime();
    }
    return 0;
    
}

EventQueue::~EventQueue()
{
    for (auto& event : events)
    {
        delete event;
    }
}