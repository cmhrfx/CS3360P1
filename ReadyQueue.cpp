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
    Process* poppedProcess = queue.front();
    queue.pop_front();
    return poppedProcess;
}

bool ReadyQueue::isEmpty()
{
    return queue.empty();
}

int ReadyQueue::size()
{
    return queue.size();
}