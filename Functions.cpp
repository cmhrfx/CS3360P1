#include "Functions.h"


// argChecks() checks that the necessary cmdline input
// meets specifications.
// argv[0] = program name
// argv[1] = Arrival Rate float
// argv[2] = Service Time float
// argv[3] = Logging output path
int argChecks(int argc, char* argv[])
{
    int flag = 0;
    if (argc > 4 || argc < 3)
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

// function for console output from bad cmdline args
void argChecktoConsole(int flag)
{
    if (flag == 1)
        {cout << "Incorrect number of arguments. Please try again.\n";}
    else if (flag == 2)
        {cout << "Incorrect type of argument. Please try again.\n";}
    else if (flag == 3)
        {cout << "Argument out of range. Please try again.\n";}
}

// handleArrival() is a core function of the Discrete Time Event Simulator engine.
// Called when current Event is an arrival.
// Based on the cpu_status, one of two paths will be taken:
// if cpu_status is 0, the new arrival event is converted immediately into a new 
// departure event. cpu_status is also flipped to 1. 
// if cpu_status is 1, the new arrival event is converted into a process placed
// in the ready queue.
// In both cases, the next arrival event is created from the ProcessList and added
// to the event queue. 
void handleArrival(Event* event)
{
    core.arrivals++;

    // Path 1- idle CPU
    if (core.cpu_status == 0)
    {
        core.cpu_status = 1;
        float interval = event->process->serviceTime + core.time_piece;
        Event* newDeparture = new Event(event->process, interval, "departure");
        core.eq.scheduleEvent(newDeparture);
    }
    // Path 2- busy CPU
    else
    {
        core.rq.addProcess(event->process);
    }

    // Both paths end in the creation of a new arrival event from ProcessList
    Process* nextProcess = core.processes.popProcess();
    // Check that ProcessList isn't empty
    if (nextProcess == nullptr)
    {
        core.processes_empty = true;
    }
    else
    {
        Event* newArrival = new Event(nextProcess, nextProcess->arrivalTime, "arrival");
        core.eq.scheduleEvent(newArrival);
    }

}


// handleDeparture() is a core function of the Discrete Time Event Simulator engine.
// Called when the current event is a departure. 
// Based on the ready_queue, one of two paths will be taken.
// If ready_queue is empty, cpu_status is set to 0. 
// If ready_queue contains a process, it is popped and a new departure event 
// is made of that process.

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

// handlePoll() is key to quantifying metrics of the DTES.
// Upon instantiation, the Event Queue contains a first instance of a poll event.
// When this first instance is processed, handlePoll then schedules a following
// poll event. This process repeats until the Process Queue is empty.
// Variables under the global "core" struct are used to track these metrics.
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


// outputMetrics() is used to compose console output of performance metrics
// post-loop-completion.
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

// logMetrics() is used to output performance metrics to an external log file.
// In main, 'string path' is taken from cmdline args (argv[3]).
// Output of logmetrics is in .csv format. 
void logMetrics(float arrivalRate, float serviceTime, string path)
{
    cout << "log path: " << path << endl;
    std::ofstream outFile(path, std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening log file path." << std::endl;
    }
    else
    {
        outFile << arrivalRate << "," << serviceTime << "," << (core.turnarounds / LENGTH)
        << "," << (LENGTH / core.time_piece) << "," << (core.cpu_active_count / core.sample_polls)
        << "," << (core.sample_queue / core.sample_polls) << endl;
        outFile.close();
        cout << "Results written to logs" << endl;
    }
}