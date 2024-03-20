#ifndef PROCESS_H
#define PROCESS_H



class Process{
public:
    Process(int id, float arrivalTime, float serviceTime);
    int id;
    float arrivalTime;
    float serviceTime;
};


#endif