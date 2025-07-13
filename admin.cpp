#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

struct Complaint {
    int id;
    std::string username;
    std::string title;
    std::string description;
    std::string category;
    std::string location;
    std::string status;
    int priority;
    std::string timestamp;
};

bool Admin::login() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::getline(std::cin, username);
    std::cout << "Enter admin password: ";
    std::getline(std::cin, password);

    if (username == "admin" && password == "admin@123") {
        std::cout << "\n Admin login successful!\n";
        return true;
    }

    std::cout << "\n Invalid admin credentials.\n";
    return false;
}

bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void Admin::showPanel() {
    std::ifstream file("complaints.txt");
    std::vector<Complaint> complaints;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string fields[9];
        for (int i = 0; i < 9 && std::getline(ss, fields[i], '|'); ++i);

        // Check if all 9 fields are present
        bool hasAllFields = true;
        for (int i = 0; i < 9; ++i) {
            if (fields[i].empty()) {
                hasAllFields = false;
                break;
            }
        }

        if (!hasAllFields || !isNumeric(fields[0]) || !isNumeric(fields[5])) {
            std::cerr << "\n Skipping invalid line (missing or bad fields):\n" << line << "\n";
            continue;
        }

        Complaint c;
        c.id = std::stoi(fields[0]);
        c.username = fields[1];
        c.title = fields[2];
        c.description = fields[3];
        c.category = fields[4];
        c.priority = std::stoi(fields[5]);
        c.location = fields[6];
        c.timestamp = fields[7];
        c.status = fields[8];

        complaints.push_back(c);
    }
    file.close();

    if (complaints.empty()) {
        std::cout << "\n No valid complaints found in complaints.txt\n";
        return;
    }

    // Sort by priority
    std::sort(complaints.begin(), complaints.end(), [](const Complaint& a, const Complaint& b) {
        return a.priority > b.priority;
    });

    std::cout << "\n=== 📋 COMPLAINT LIST (Sorted by Priority) ===\n";
    for (size_t i = 0; i < complaints.size(); ++i) {
        std::cout << "\nComplaint #" << i + 1 << "\n";
        std::cout << "ID: " << complaints[i].id << "\n";
        std::cout << "User: " << complaints[i].username << "\n";
        std::cout << "Title: " << complaints[i].title << "\n";
        std::cout << "Description: " << complaints[i].description << "\n";
        std::cout << "Category: " << complaints[i].category << "\n";
        std::cout << "Priority: " << complaints[i].priority << "\n";
        std::cout << "Location: " << complaints[i].location << "\n";
        std::cout << "Timestamp: " << complaints[i].timestamp << "\n";
        std::cout << "Status: " << complaints[i].status << "\n";
        std::cout << "-----------------------------\n";
    }

    int select;
    std::cout << "\nEnter complaint number to review (0 to exit): ";
    std::cin >> select;
    std::cin.ignore();

    if (select <= 0 || select > complaints.size()) {
        std::cout << "\nReturning to main menu...\n";
        return;
    }

    char decision;
    std::cout << "Approve (y) or Reject (n) complaint ID "
              << complaints[select - 1].id << "? ";
    std::cin >> decision;
    std::cin.ignore();

    if (decision == 'y' || decision == 'Y') {
        complaints[select - 1].status = "Approved";
    } else if (decision == 'n' || decision == 'N') {
        complaints[select - 1].status = "Rejected";
    } else {
        std::cout << "Invalid input. No changes made.\n";
        return;
    }

    // Save changes
    std::ofstream outfile("complaints.txt");
    for (const auto& c : complaints) {
        outfile << c.id << "|" << c.username << "|" << c.title << "|"
                << c.description << "|" << c.category << "|" << c.priority
                << "|" << c.location << "|" << c.timestamp << "|" << c.status << "\n";
    }
    outfile.close();

    std::cout << "\n Complaint status updated successfully!\n";
}
