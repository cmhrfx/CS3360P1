#include "Functions.h"

extern EventQueue* eq;
extern ReadyQueue* rq;
extern ProcessList* processes;
extern float* clock;
extern int* cpu_status;
extern int* counter;

int argChecks(int argc, char* argv[])
{
    int flag = 0;
    if (argc != 3)
    {
        // incorrect number of arguments
        flag = 1;
    }
    else
    {
        try {
            float intValue = std::stof(argv[1]);
            float floatValue = std::stof(argv[2]);
        } 
        // catch for type mismatch
        catch (const std::invalid_argument& ia)
        {
            flag = 2;
        }
        // catch for range mismatch
        catch (const std::out_of_range& oor)
        {
            flag = 3;
        }
    }
    return flag;
}

void argChecktoConsole(int flag)
{
    if (flag == 1)
    {
        std::cout << "Incorrect number of arguments. Please try again.";
    }
    else if (flag == 2)
    {
        std::cout << "Incorrect type of argument. Please try again.";
    }
    else if (flag == 3)
    {
        std::cout << "Argument out of range. Please try again.";
    }
    // No output for other flags
}

void handle_arrival(Event* event)
{
    Process* currentProcess = event->getEventProcess();

    if (*cpu_status == 0)
    {
        *cpu_status = 1;
        float interval = currentProcess->getServiceTime() + *clock;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        eq->scheduleEvent(newDeparture);
    }
    else
    {
        rq->addProcess(currentProcess);
    }
    Process* nextProcess = processes->getProcess(*counter);
    Event* newArrival = new Event(nextProcess, nextProcess->getArrivalTime(), "arrival");
    eq->scheduleEvent(newArrival);
}

void handle_departure (Event* event)
{
    if (rq->isEmpty())
    {
        *cpu_status = 0;
    }
    else
    {
        Process* currentProcess = rq->popFront();
        float interval = currentProcess->getServiceTime() + *clock;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        eq->scheduleEvent(newDeparture);
    }
}


bool tick(Event* event)
{
    bool queueEmpty = false;
    Event* event = eq->getEvent();
    
    if (event == nullptr)
    {
        queueEmpty = true;
    }
    else
    {
        if (event->getEventType() == "arrival")
        {
            handle_arrival(event);
        }
        else if (event->getEventType() == "departure")
        {
            handle_departure(event);
        }
    }
    
}