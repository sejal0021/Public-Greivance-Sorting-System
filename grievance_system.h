#ifndef GRIEVANCE_SYSTEM_H
#define GRIEVANCE_SYSTEM_H

#include <vector>
#include <queue>
#include "grievance.h"

class PriorityComparator {
public:
    bool operator()(const Grievance& a, const Grievance& b) const {
        if (a.getPriority() == b.getPriority()) {
            return a.getTimestamp() > b.getTimestamp(); // older one first
        }
        return a.getPriority() < b.getPriority(); // high priority on top
    }
};

class GrievanceSystem {
private:
    std::vector<Grievance> grievances;
    std::priority_queue<Grievance, std::vector<Grievance>, PriorityComparator> priorityQueue;

public:
    void run();
    void loadFromFile();               // Load from complaints.txt
    void addSampleGrievances();       // For testing
    void displayAllGrievances();      
    void displayByPriority();
    void displayByCategory();
    void updateGrievanceStatus();
    void searchGrievanceById();
    void displayStatistics();
    void sortByTimestamp();
};

#endif
