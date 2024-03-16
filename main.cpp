/*
Christopher Hanly
Homework 4
CS 3360 Computing Systems Fundamentals
Guirguis
03/14/24

#################################################

In this project, a Discrete Time Event simulator is created.
The program takes two arguments at the command line: average arrival time
and average service time. The average arrival time denotes a Poisson
distribution and the average service time denotes an Exponential distribution.

A list of processes of length 10,000 will be instantiated. That list will 
then be checked every clock tick to see if a new process should be introduced
to the Ready Queue. 

Furthermore, each clock tick will be used to determine if an event in the
Ready Queue should be introduced to the Event Queue.
*/

#include "main.h"

// Declaring some global variables for externalization
float* time_piece = new float(0);       // global clock
int* cpu_status = new int(0);           // 0 = not busy, 1 = busy
int* sample_queue = new int(0);         // x += number of processes in rq
int* sample_polls = new int(0);         // track number of polls
int* counter = new int(0);              // counter to tick through processes
ReadyQueue* rq = new ReadyQueue();      // instantiated as empty
EventQueue* eq = new EventQueue();      // instantiated with 1 initial departure event
bool debug = true;                      // turn on debugging output


int main(int argc, char *argv[])
{
    // It's generally not good practice to place a separate return statement, but
    // I believe this is acceptable when we're doing an early arg check.
    // This way, I don't need to nest the entire driver logic under 
    // "if (argFailure != 0)"

    int flag = argChecks(argc, argv);   // check for correct number of args

    if (flag > 0)
    {
        return 1;                   // Ends program early if a bad argument occurred.
    }

    // ######################################################################
    // Okay moving on to main driver logic

    // Pull out cmdline arguments and capture them as variables
    float arrivalLambda = std::stof(argv[1]);
    float serviceLambda = std::stof(argv[2]);

    // instantiate all 1000 processes into a list
    ProcessList* processes = new ProcessList(arrivalLambda, serviceLambda);
    // processes.listToConsole();   // for testing during development

    bool complete = false;
    

    while (!complete)
    {
        // FKA "tick"
        Event* event = eq->getEvent();
        if (debug)
        {
            cout << "Beginning tick" << endl;
            cout << event->getEventProcessId() << endl;
            cout << event->getEventTime() << endl;
            cout << event->getEventType() << endl;
        }
        if (event == nullptr)
            {
                if (debug)
                {
                    cout << "event = nullptr";
                }
                complete = true;
            }
        else
        {
            if (event->getEventType() == "arrival")
                {handle_arrival(event, processes);}
                
            else if (event->getEventType() == "departure")
                {handle_departure(event, processes);}
                
            else if (event->getEventType() == "poll")
                {handle_poll(event, processes);}
        }

        if (debug)
        {
            cout << "Ending tick" << endl;
            cout << event->getEventProcessId() << endl;
            cout << event->getEventTime() << endl;
            cout << event->getEventType() << endl;
        }
    }
    


    return 0;
}
