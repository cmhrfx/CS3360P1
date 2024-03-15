#include "Process.h"

Process::Process(int id, float arrivalTime, float serviceTime)
{
    this->id = id;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
};

int Process::getId() const
{
    return id;
}

float Process::getArrivalTime() const
{
    return arrivalTime;
}

float Process::getServiceTime() const
{
    return serviceTime;
}

