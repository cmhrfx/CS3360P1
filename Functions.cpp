#include "Functions.h"

int argChecks(int argc, char* argv[])
{
    if (DEBUG)
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

    if (DEBUG)
    {
        cout << "Completed argchecks" << endl;
    }
    return flag;
}

void argChecktoConsole(int flag)
{
    if (DEBUG)
    {
        cout << "Running argChecktoConsole" << endl;
    }
    if (flag == 1)
    {
        std::cout << "Incorrect number of arguments. Please try again.\n";
    }
    else if (flag == 2)
    {
        std::cout << "Incorrect type of argument. Please try again.\n";
    }
    else if (flag == 3)
    {
        std::cout << "Argument out of range. Please try again.\n";
    }
    // No output for other flags

    if (DEBUG)
    {
        cout << "Completed argChecktoConsole" << endl;
    }
}

void handleArrival(Event* event)
{
    if (DEBUG)
    {
        cout << "Running handle_arrival" << endl;
    }
    Process* currentProcess = event->getEventProcess();

    if (core.cpu_status == 0)
    {
        core.cpu_status = 1;
        float interval = currentProcess->getServiceTime() + core.time_piece;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        core.eq.scheduleEvent(newDeparture);
    }
    else if (event->getEventProcessId() != 0)
    {
        core.rq.addProcess(currentProcess);
    }
    core.counter++;
    Process* nextProcess = core.processes.getProcess();
    Event* newArrival = new Event(nextProcess, nextProcess->getArrivalTime(), "arrival");
    Process* pollProcess = new Process(-1, 0, 0);
    Event* newPoll = new Event(pollProcess, 0, "poll");
    core.eq.scheduleEvent(newPoll);
    core.eq.scheduleEvent(newArrival);

    if (DEBUG)
    {
        cout << "Completed handle_arrival" << endl;
    }
}

void handleDeparture (Event* event)
{
    if (DEBUG)
    {
        cout << "Running handle_departure" << endl;
    }
    if (core.rq.isEmpty())
    {
        core.cpu_status = 0;
    }
    else
    {
        Process* currentProcess = core.rq.popFront();
        float interval = currentProcess->getServiceTime() + core.time_piece;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        core.eq.scheduleEvent(newDeparture);
    }

    if (DEBUG)
    {
        cout << "Completed handle_departure" << endl;
    }
}

void handlePoll (Event* event)
{
    if (DEBUG)
    {
        cout << "Running handle_poll" << endl;
    }
    core.sample_queue += core.rq.size();
    core.sample_polls += 1;
    if (DEBUG)
    {
        cout << "Completed handle_poll" << endl;
    }
}
