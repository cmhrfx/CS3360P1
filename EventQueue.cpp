#include "EventQueue.h"

EventQueue::EventQueue()
{
    Event* initiate = new Event(0,0,"arrival");
    events.push_back(initiate);
};

void EventQueue::addEvent(Event* event)
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