#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <string>

struct Process {
    std::string name;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

class Scheduler {
private:
    std::vector<Process> processes;
    int timeQuantum;

public:
    Scheduler(int quantum = 2); // default 2 units
    void addProcess(const std::string& name, int burstTime);
    void runRoundRobin();
};

#endif
