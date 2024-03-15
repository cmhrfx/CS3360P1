#ifndef PROCESS_H
#define PROCESS_H


class Process{
public:
    Process(int id, float arrivalTime, float serviceTime);
    int getId() const;
    float getArrivalTime() const;
    float getServiceTime() const;

private:
    int id;
    float arrivalTime;
    float serviceTime;
};


#endif