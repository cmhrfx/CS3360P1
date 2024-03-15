#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "Process.h"
#include <list>

class ReadyQueue{
public:
    ReadyQueue();
    void addProcess(Process* newProcess);
    Process* popFront();
    bool isEmpty();
    int size();
    
private:
    std::list<Process*> queue;
};



#endif