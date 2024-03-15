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
}

void handleArrival(EventQueue* eq, ReadyQueue* rq, Event* event, int cpu_status)
{

}

void handleDeparture(EventQueue* eq, ReadyQueue* rq, Event* event, int cpu_status)
{
    
}


bool tick(EventQueue* eq, ReadyQueue* rq, Event* event, int counter, float* clock, int cpu_status)
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
            handle_arrival
        }
    }
    
}