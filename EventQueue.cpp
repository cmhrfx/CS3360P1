#include "EventQueue.h"

EventQueue::EventQueue()
{
    Process* initiationProcess = new Process(0,0,0);
    Event* initiationEvent = new Event(initiationProcess,0,"arrival");
    Process* initialPollProcess = new Process(-1,0,0);
    Event* initiationPoll = new Event(initialPollProcess,0.1,"poll");
    events.push_back(initiationEvent);
    events.push_back(initiationPoll);
};


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

void EventQueue::scheduleEvent(Event* newEvent)
{
    if (events.empty() || newEvent->getEventTime() < events.front()->time)
    {
        events.push_front(newEvent);
    } else {
        std::list<Event*>::iterator it = events.begin();

        while (it != events.end() && newEvent->getEventTime() >= (*it)->time)
        {
            ++it;
        }
        events.insert(it, newEvent);
    }
}

EventQueue::~EventQueue()
{
    for (auto& event : events)
    {
        delete event;
    }
}