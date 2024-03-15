#ifndef EVENT_H
#define EVENT_H

#include <string>

using std::string;

// For ease with switch, using integers for type
// 0 = departure, 1 = arrival
class Event{
public:
    Event(int pid, float time, std::string type);
    float getEventTime() const;
    int getEventProcessId() const;
    string getEventType() const;

private:
    int pid;
    float time;
    string type;
};



#endif