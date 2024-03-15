#include "ReadyQueue.h"

ReadyQueue::ReadyQueue()
{

};

void ReadyQueue::addProcess(Process* newProcess)
{
    queue.push_back(newProcess);
}

Process* ReadyQueue::popFront()
{
    queue.pop_front();
}

bool ReadyQueue::isEmpty()
{
    return queue.empty();
}