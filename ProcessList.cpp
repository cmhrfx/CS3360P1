#include "ProcessList.h"

// populate processList on instantiation
ProcessList::ProcessList(float arrivalRate, float serviceTime)
{
    populateList(arrivalRate, serviceTime);
}

ProcessList::ProcessList()
{
    populateList(1,1);
}

// lambda is the rate of instances over a fixed length of time.
// Thus, for arrivals, we can use the flat value (e.g. lambda = 10)
// However, for service times, we are given the unit of 0.04s service time.
// By dividing 1/ avg service time, we can transform the service time to a
// poisson lambda (ie a rate). 
float ProcessList::genExponentialRandom(float lambda)
{
    float random = rand() / (RAND_MAX + 1.0);
    return -log(1 - random) / lambda;
}

// populate the ProcessList with proceses
// use genExponentialRandom with different lambdas to instantiate a process
// then push that processes onto the list. Repeat for length required.
void ProcessList::populateList(float arrivalRate, float serviceTime)
{
    float generationTime = 0;
    srand(time(0));
    for (int i = 0; i < core.LENGTH; i++)
    {
        float interArrivalTime = genExponentialRandom(arrivalRate);
        generationTime += interArrivalTime;
        Process* newProcess = new Process(i + 1, generationTime, genExponentialRandom(1/serviceTime));
        processes.push_back(newProcess);
    }
}

// Console output of ProcessList, made for testing during development
void ProcessList::listToConsole()
{
    std::cout   << std::left << std::setw(12) << "Process ID"
                << std::setw(15) << "Arrival Time"
                << std::setw(15) << "Service Time"
                << std::endl;
    std::cout   << std::string(42, '-') << std::endl;

    for (const auto& process : processes)
    {
        std::cout << std::left << std::setw(12) << process->id
                  << std::setw(15) << process->arrivalTime
                  << std::setw(15) << process->serviceTime
                  << std::endl;
    }
}

// popProcess() cleanly returns the front element of a ProcessList and 
// then removes it from that list. 
Process* ProcessList::popProcess()
{
    Process* process = nullptr;
    if (!processes.empty())
    {
        process = processes.front();
        processes.pop_front();
    }
    return process;
}

// Return if the process list is empty 
// originally made when 'processes' property was private
bool ProcessList::isEmpty()
{
    return processes.empty();
}

// Default Destructor
ProcessList::~ProcessList()
{
    for (Process* process : processes) {
        delete process;
    }
    processes.clear();
}

