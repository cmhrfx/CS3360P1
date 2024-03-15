#include "Event.h"

Event::Event(int pid, float time, string type)
{
    this->pid = pid;
    this->time = time;
    this->type = type;
};

float Event::getEventTime() const
{
    return time;
}

int Event::getEventProcessId() const
{
    return pid;
}

string Event::getEventType() const
{
    return type;
}
