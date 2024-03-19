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
        {cout << "Running argChecktoConsole" << endl;}
    if (flag == 1)
        {cout << "Incorrect number of arguments. Please try again.\n";}
    else if (flag == 2)
        {cout << "Incorrect type of argument. Please try again.\n";}
    else if (flag == 3)
        {cout << "Argument out of range. Please try again.\n";}
    if (DEBUG)
        {cout << "Completed argChecktoConsole" << endl;}
}

void handleArrival(Event* event)
{
    if (DEBUG)
    {
        cout << "Running handle_arrival" << endl;
    }

    Event* newArrival = new Event();
    Event* newDeparture = new Event();

    core.arrivals++;
    Process* currentProcess = event->getEventProcess();

    if (core.cpu_status == 0)
    {
        core.cpu_status = 1;
        float interval = currentProcess->getServiceTime() + core.time_piece;
        newDeparture = new Event(currentProcess, interval, "departure");
        core.eq.scheduleEvent(newDeparture, event);
    }
    else
    {
        core.rq.addProcess(currentProcess);
    }

    Process* nextProcess = core.processes.getProcess();
    if (nextProcess == nullptr)
    {
        core.processes_empty = true;
    }
    else 
    {
        newArrival = new Event(nextProcess, nextProcess->getArrivalTime(), "arrival");
        core.eq.scheduleEvent(newArrival, newDeparture);
    }
    schedulePoll();

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
    core.departures++;
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

    core.poll_period++;

    if(core.poll_period%5 == 1)
    {
        core.sample_queue += core.rq.size();
        core.sample_polls++;
    }

    if (DEBUG)
    {
        cout << "Completed handle_poll" << endl;
    }
}

void schedulePoll()
{
    Process* pollProcess = new Process(-1, 0, 0);
    Event* newPoll = new Event(pollProcess, 0, "poll");
    core.eq.scheduleEvent(newPoll);
}