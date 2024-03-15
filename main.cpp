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

int main(int argc, char *argv[])
{
    // It's generally not good practice to place a separate return statement, but
    // I believe this is acceptable when we're doing an early arg check.
    // This way, I don't need to nest the entire driver logic under 
    // "if (argFailure != 0)"

    // Checking that the appropriate number and type of arguments are made.
    int flag = argChecks(argc, argv);
    // Generates console output to communicate bad argument occurrence
    argChecktoConsole(flag);

    // Ends program early if a bad argument occurred.
    if (flag > 0)
    {
        return 1;
    }

    // ######################################################################
    // Okay moving on to main driver logic

    // Pull out cmdline arguments and capture them as variables
    float arrivalLambda = std::stof(argv[1]);
    float serviceLambda = std::stof(argv[2]);

    // instantiate clock, ready queue, and CPU
    float clock = 0;
    float idleTime = 0;
    bool cpu_busy = false;
    bool exit = false;
    ReadyQueue rq;
    EventQueue eq;
    ProcessList processes(arrivalLambda, serviceLambda);
    // for testing during development
    // processes.listToConsole();

    


    return 0;
}
