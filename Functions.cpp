#include "Functions.h"

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

    argChecktoConsole(flag);

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

void handle_arrival(Event* event, ProcessList* processes)
{
    Process* currentProcess = event->getEventProcess();

    if (*cpu_status == 0 && event->getEventProcessId() != 0)
    {
        *cpu_status = 1;
        float interval = currentProcess->getServiceTime() + *clock;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        eq->scheduleEvent(newDeparture);
    }
    else if (event->getEventProcessId() != 0)
    {
        rq->addProcess(currentProcess);
    }
    Process* nextProcess = processes->getProcess(*counter);
    Event* newArrival = new Event(nextProcess, nextProcess->getArrivalTime(), "arrival");
    Process* pollProcess = new Process(-1, 0, 0);
    Event* newPoll = new Event(pollProcess, 0, "poll");
    eq->scheduleEvent(newPoll);
    eq->scheduleEvent(newArrival);
}

void handle_departure (Event* event, ProcessList* processes)
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

void handle_poll (Event* event, ProcessList* processes)
{
    *sample_queue += rq->size();
    *sample_polls += 1;
}


void tick(Event* event, ProcessList* processes)
{
    Event* event = eq->getEvent();
    
    if (event == nullptr)
    {
        *exit = true;
    }
    else
    {
        if (event->getEventType() == "arrival")
        {
            handle_arrival(event, processes);
        }
        else if (event->getEventType() == "departure")
        {
            handle_departure(event, processes);
        }
        else if (event->getEventType() == "poll")
        {
            handle_poll(event, processes);
        }
    }
    
}