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

A list of processes of length 10,000 will be instantiated and processed into
an Event Queue. Three possible events exist: arrival, departure, and poll.

The Event Queue is instantiated with an initial arrival "base case" to start
the loop. Each time an arrival event is handled, a new arrival event is pulled
from the Process List. This process continues until both the Process List
and Event Queues are empty. 
*/

#include "main.h"
// GLOBALS
Core core;                                      // struct for global variables
float const LENGTH = 10000;                     

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
    float arrivalRate = std::stof(argv[1]);
    float serviceTime = std::stof(argv[2]);

    // output stream for key result information
    

    // instantiate process list with user arguments, then assign to global struct
    ProcessList processes(arrivalRate, serviceTime);
    core.processes = processes;

    // Core function loop
    while (!core.events_empty)
    {
        // Evaluate if EventQueue is empty
        if (core.eq.events.empty())
        {
            core.events_empty = true;
        }
                
        else {
            // Pop the event from front of EventQueue and set time to event
            Event* event = core.eq.getEvent();
            core.time_piece = event->time;

            // switch logic based on event type
            if (event->type == "arrival")
                {handleArrival(event);}
                
            else if (event->type == "departure")
                {handleDeparture(event);}
                
            else if (event->type == "poll")
                {handlePoll(event);}
        }
        
    }

    outputMetrics(arrivalRate, serviceTime);
    if (argc == 4)
    {
        logMetrics(arrivalRate, serviceTime, argv[3]);
    }

    return 0;
}
