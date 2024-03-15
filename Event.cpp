#include "Event.h"

Event::Event(Process* process, float time, string type)
{
    this->process = process;
    this->time = time;
    this->type = type;
};

Process* Event::getEventProcess()
{
    return process;
}

float Event::getEventTime() const
{
    return time;
}


string Event::getEventType() const
{
    return type;
}

int Event::getEventProcessId() const
{
    return process->getId();
}

float Event::getEventProcessAT() const
{
    return process->getArrivalTime();
}

float Event::getEventProcessST() const
{
    return process->getServiceTime();
}