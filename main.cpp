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
// GLOBALS
Core core;                                    // struct for global variables
bool const DEBUG = false;                      // turn on debugging output
int const LENGTH = 10000;

int main(int argc, char *argv[])
{
    // It's generally not good practice to place a separate return statement, but
    // I believe this is acceptable when we're doing an early arg check.
    // This way, I don't need to nest the entire driver logic under 
    // "if (argFailure != 0)"

    /*
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

    */

    // instantiate all processes into a list
    float arrivalLambda = 10;
    float serviceLambda = 0.04;
    ProcessList processes(arrivalLambda, serviceLambda);
    core.processes = processes;    
    // core.processes.listToConsole();

    while (!core.events_empty)
    {
        // FKA "tick"
        Event* event = core.eq.getEvent();
        if (event == nullptr)
        {
            core.events_empty = true;
        }
        else {
            core.time_piece = event->getEventTime();

            if (DEBUG && event->getEventType() != "poll")
            {
                cout << "Beginning tick" << endl;
                cout << "Event ProcessID: " << event->getEventProcessId() << endl;
                cout << "Event Time: " << event->getEventTime() << endl;
                cout << "Event Type: " << event->getEventType() << endl;
                cout << "Event Process Arrival Time: " << event->getEventProcessAT() << endl;
                cout << "Event Process Service Time: " << event->getEventProcessST() << endl;
            }

            if (event->getEventType() == "arrival")
                {handleArrival(event);}
                
            else if (event->getEventType() == "departure")
                {handleDeparture(event);}
                
            else if (event->getEventType() == "poll")
                {handlePoll(event);}
        }
        

    /*
        if (DEBUG)
        {
            cout << "Event Process Id: " << event->getEventProcessId() << endl;
            cout << "Event Time: " << event->getEventTime() << endl;
            cout << "Event Type: " << event->getEventType() << endl;
            cout << "Ending tick" << endl;
        }
    */
    }
    
    // post loop stats
    cout << "Number of polls: " << core.sample_polls << endl;
    cout << "Number of arrivals: " << core.arrivals - 1<< endl;
    cout << "Number of departures: " << core.departures - 1 << endl;
    cout << "Average queue length: " << core.sample_queue / core.sample_polls << endl;

    return 0;
}
