#include "../include/Scheduler.hpp"
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <string>

Scheduler::Scheduler(int quantum) : timeQuantum(quantum) {}

void Scheduler::addProcess(const std::string& name, int burstTime) {
    Process p = { name, burstTime, burstTime, 0, 0 };
    processes.push_back(p);
}

void Scheduler::runRoundRobin() {
    std::queue<int> readyQueue;
    for (size_t i = 0; i < processes.size(); ++i) {
        readyQueue.push(i);
    }

    int time = 0;
    std::cout << "\n== 🧠 Running Round Robin Scheduler ==\n";
    std::cout << "Time Quantum: " << timeQuantum << " units\n";

    std::cout << "\n🕒 Gantt Chart:\n";

    while (!readyQueue.empty()) {
        size_t idx = readyQueue.front();
        readyQueue.pop();

        Process& p = processes[idx];

        int executeTime = std::min(timeQuantum, p.remainingTime);
        std::cout << "[" << time << "]--(" << p.name << ")--";
        time += executeTime;
        std::cout << "[" << time << "] ";

        p.remainingTime -= executeTime;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (i != idx && processes[i].remainingTime > 0) {
                processes[i].waitingTime += executeTime;
            }
        }

        if (p.remainingTime > 0) {
            readyQueue.push(idx);
        } else {
            p.turnaroundTime = time;
        }
    }

    std::cout << "\n\n📊 Result Table:\n";
    std::cout << std::left << std::setw(10) << "Process" 
              << std::setw(15) << "Waiting Time" 
              << "Turnaround Time\n";

    for (const auto& p : processes) {
        std::cout << std::left << std::setw(10) << p.name 
                  << std::setw(15) << p.waitingTime 
                  << p.turnaroundTime << "\n";
    }



    float totalWait = 0, totalTurnaround = 0;
    for (const auto& p : processes) {
        totalWait += p.waitingTime;
        totalTurnaround += p.turnaroundTime;
    }
    std::cout << "\n📈 Avg Waiting Time: " << totalWait / processes.size() << "\n";
    std::cout << "\n📈 Avg Turnaround Time: " << totalTurnaround / processes.size() << "\n";    

}
