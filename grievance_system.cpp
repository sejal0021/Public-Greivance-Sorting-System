// grievance_system.cpp - Full Working Version

#include "grievance_system.h"
#include "grievance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

void GrievanceSystem::loadFromFile() {
    grievances.clear();
    while (!priorityQueue.empty()) priorityQueue.pop();

    std::ifstream file("complaints.txt");
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, username, title, desc, category, priorityStr, location, timestamp, status;

        getline(ss, idStr, '|');
        getline(ss, username, '|');
        getline(ss, title, '|');
        getline(ss, desc, '|');
        getline(ss, category, '|');
        getline(ss, priorityStr, '|');
        getline(ss, location, '|');
        getline(ss, timestamp, '|');
        getline(ss, status, '|');

        if (idStr.empty() || priorityStr.empty()) continue;

        Grievance g;
        g.setId(std::stoi(idStr));
        g.setUsername(username);
        g.setTitle(title);
        g.setDescription(desc);
        g.setCategory(category);
        g.setPriority(std::stoi(priorityStr));
        g.setLocation(location);
        g.setTimestamp(timestamp);
        g.setStatus(status);

        grievances.push_back(g);
        priorityQueue.push(g);
    }
    file.close();
}

void GrievanceSystem::run() {
    loadFromFile();
    int choice;

    while (true) {
        std::cout << "\n=== PUBLIC GRIEVANCE SORTING SYSTEM ===\n";
        std::cout << "1. Add New Grievance (Sample)\n";
        std::cout << "2. Display All Grievances\n";
        std::cout << "3. Display Grievances by Priority\n";
        std::cout << "4. Display Grievances by Category\n";
        std::cout << "5. Update Grievance Status\n";
        std::cout << "6. Search Grievance by ID\n";
        std::cout << "7. Display Statistics\n";
        std::cout << "8. Display Grievances by Timestamp\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                addSampleGrievances();
                break;
            case 2:
                displayAllGrievances();
                break;
            case 3:
                displayByPriority();
                break;
            case 4:
                displayByCategory();
                break;
            case 5:
                updateGrievanceStatus();
                break;
            case 6:
                searchGrievanceById();
                break;
            case 7:
                displayStatistics();
                break;
            case 8:
                sortByTimestamp();
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void GrievanceSystem::addSampleGrievances() {
    grievances.clear();
    grievances.push_back(Grievance(1, "arsh", "Water Issue", "No water in area", "Water", 5, "Ludhiana", "2025-07-10 10:00:00", "Pending"));
    grievances.push_back(Grievance(2, "karan", "Power Cut", "Frequent outages", "Electricity", 4, "Jalandhar", "2025-07-10 11:00:00", "Pending"));
    grievances.push_back(Grievance(3, "mandeep", "Road Damage", "Potholes everywhere", "Infrastructure", 3, "Amritsar", "2025-07-09 09:00:00", "Pending"));
    grievances.push_back(Grievance(4, "simran", "Garbage", "No garbage pickup", "Environment", 2, "Bathinda", "2025-07-08 08:00:00", "Pending"));

    std::ofstream file("complaints.txt");
    for (const auto& g : grievances) {
        file << g.getId() << "|" << g.getUsername() << "|" << g.getTitle() << "|" << g.getDescription() << "|"
             << g.getCategory() << "|" << g.getPriority() << "|" << g.getLocation() << "|"
             << g.getTimestamp() << "|" << g.getStatus() << "\n";
    }
    file.close();
    std::cout << "Sample grievances added successfully!\n";
}

void GrievanceSystem::displayAllGrievances() {
    if (grievances.empty()) {
        std::cout << "No grievances found.\n";
        return;
    }
    std::cout << "\n=== ALL GRIEVANCES ===\n";
    for (const auto& g : grievances) {
        g.display();
        std::cout << "------------------------\n";
    }
}

void GrievanceSystem::displayByPriority() {
    if (priorityQueue.empty()) {
        std::cout << "No grievances to sort.\n";
        return;
    }
    std::priority_queue<Grievance, std::vector<Grievance>, PriorityComparator> temp = priorityQueue;
    std::cout << "\n=== GRIEVANCES SORTED BY PRIORITY ===\n";
    while (!temp.empty()) {
        temp.top().display();
        std::cout << "------------------------\n";
        temp.pop();
    }
}

void GrievanceSystem::displayByCategory() {
    std::string cat;
    std::cout << "Enter category to filter: ";
    std::getline(std::cin, cat);
    bool found = false;
    for (const auto& g : grievances) {
        if (g.getCategory() == cat) {
            g.display();
            std::cout << "------------------------\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "No grievances found in this category.\n";
}

void GrievanceSystem::updateGrievanceStatus() {
    int id;
    std::cout << "Enter grievance ID to update: ";
    std::cin >> id;
    std::cin.ignore();
    for (auto& g : grievances) {
        if (g.getId() == id) {
            std::string status;
            std::cout << "Enter new status (Pending/Approved/Rejected): ";
            std::getline(std::cin, status);
            g.setStatus(status);
            std::cout << "Status updated.\n";
            return;
        }
    }
    std::cout << "Grievance not found.\n";
}

void GrievanceSystem::searchGrievanceById() {
    int id;
    std::cout << "Enter grievance ID to search: ";
    std::cin >> id;
    std::cin.ignore();
    for (const auto& g : grievances) {
        if (g.getId() == id) {
            g.display();
            return;
        }
    }
    std::cout << "Grievance not found.\n";
}

void GrievanceSystem::displayStatistics() {
    std::map<std::string, int> categoryCount;
    std::map<std::string, int> statusCount;
    for (const auto& g : grievances) {
        categoryCount[g.getCategory()]++;
        statusCount[g.getStatus()]++;
    }
    std::cout << "\n=== CATEGORY WISE COUNT ===\n";
    for (const auto& pair : categoryCount)
        std::cout << pair.first << ": " << pair.second << "\n";

    std::cout << "\n=== STATUS WISE COUNT ===\n";
    for (const auto& pair : statusCount)
        std::cout << pair.first << ": " << pair.second << "\n";
}

void GrievanceSystem::sortByTimestamp() {
    if (grievances.empty()) {
        std::cout << "No grievances to sort.\n";
        return;
    }
    std::vector<Grievance> temp = grievances;
    std::sort(temp.begin(), temp.end(), [](const Grievance& a, const Grievance& b) {
        return a.getTimestamp() < b.getTimestamp();
    });
    std::cout << "\n=== GRIEVANCES SORTED BY TIMESTAMP ===\n";
    for (const auto& g : temp) {
        g.display();
        std::cout << "------------------------\n";
    }
}
