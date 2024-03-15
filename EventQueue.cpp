#include "EventQueue.h"

EventQueue::EventQueue()
{
    Process* initiateP = new Process(0,0,0);
    Event* initiateE = new Event(initiateP,0,"arrival");
    events.push_back(initiateE);
};

void EventQueue::scheduleEvent(Event* event)
{
    events.push_back(event);
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