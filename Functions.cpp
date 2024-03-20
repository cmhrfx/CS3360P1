#include "Functions.h"

Process* pollProcess = new Process(-1,0,0);

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
        {cout << "Incorrect number of arguments. Please try again.\n";}
    else if (flag == 2)
        {cout << "Incorrect type of argument. Please try again.\n";}
    else if (flag == 3)
        {cout << "Argument out of range. Please try again.\n";}
}

void handleArrival(Event* event)
{
    Event* newArrival = new Event();
    Event* newDeparture = new Event();
    core.arrivals++;

    if (core.cpu_status == 0)
    {
        core.cpu_status = 1;
        float interval = event->process->serviceTime + core.time_piece;
        newDeparture = new Event(event->process, interval, "departure");
        core.eq.scheduleEvent(newDeparture);
    }
    else
    {
        core.rq.addProcess(event->process);
    }

    Process* nextProcess = core.processes.popProcess();
    if (nextProcess == nullptr)
    {
        core.processes_empty = true;
    }
    else
    {
        newArrival = new Event(nextProcess, nextProcess->arrivalTime, "arrival");
        core.eq.scheduleEvent(newArrival);
    }

}

void handleDeparture(Event* event)
{
    core.departures++;
    if (core.rq.isEmpty())
    {
        core.cpu_status = 0;
    }
    else
    {
        Process* currentProcess = core.rq.popFront();
        float interval = currentProcess->serviceTime + core.time_piece;
        Event* newDeparture = new Event(currentProcess, interval, "departure");
        core.eq.scheduleEvent(newDeparture);
    }
    core.turnarounds += event->time - event->process->arrivalTime;

}

void handlePoll(Event* event)
{
    if (!core.processes_empty)
    {
        core.sample_queue += core.rq.size();
        core.sample_polls++;
        if (core.cpu_status == 1)
        {
            core.cpu_active_count++;
        }

        Event* nextPoll = new Event(core.pollProcess, 
        core.time_piece + core.polling_interval, "poll");
        core.eq.scheduleEvent(nextPoll);
    }

}

void outputMetrics(float arrivalRate, float serviceTime)
{
    float avg_turnaround = core.turnarounds / LENGTH;
    float throughput = LENGTH / core.time_piece;
    float cpu_utilization = core.cpu_active_count / core.sample_polls;
    float avg_rq = core.sample_queue / core.sample_polls;

    cout << std::fixed << std::setprecision(5);
    cout << "-----------------------------------------\n";
    cout << "| Metric             | Value           |\n";
    cout << "-----------------------------------------\n";
    cout << "| Arrival Rate       | " << setw(15) << arrivalRate << " |\n";
    cout << "| Service Time       | " << setw(15) << serviceTime << " |\n";
    cout << "| Average Turnaround | " << setw(15) << avg_turnaround << " |\n";
    cout << "| Throughput         | " << setw(15) << throughput << " |\n";
    cout << "| CPU Utilization    | " << setw(15) << cpu_utilization * 100 << "% |\n"; // Convert to percentage
    cout << "| Average RQ Length  | " << setw(15) << avg_rq << " |\n";
    cout << "-----------------------------------------\n";

}