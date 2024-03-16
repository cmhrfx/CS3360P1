#include "Functions.h"

int argChecks(int argc, char* argv[])
{
    if (debug)
    {
        cout << "Running argchecks" << endl;
    }
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

    if (debug)
    {
        cout << "Completed argchecks" << endl;
    }
    return flag;
}

void argChecktoConsole(int flag)
{
    if (debug)
    {
        cout << "Running argChecktoConsole" << endl;
    }
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

    if (debug)
    {
        cout << "Completed argChecktoConsole" << endl;
    }
}

void handle_arrival(Event* event, ProcessList* processes)
{
    if (debug)
    {
        cout << "Running handle_arrival" << endl;
    }
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

    if (debug)
    {
        cout << "Completed handle_arrival" << endl;
    }
}

void handle_departure (Event* event, ProcessList* processes)
{
    if (debug)
    {
        cout << "Running handle_departure" << endl;
    }
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

    if (debug)
    {
        cout << "Completed handle_departure" << endl;
    }
}

void handle_poll (Event* event, ProcessList* processes)
{
    if (debug)
    {
        cout << "Running handle_poll" << endl;
    }
    *sample_queue += rq->size();
    *sample_polls += 1;
    if (debug)
    {
        cout << "Completed handle_poll" << endl;
    }
}
