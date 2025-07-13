#include "grievance_submission.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>

// Generate unique ID by finding max ID in file
int generateComplaintID() {
    std::ifstream file("complaints.txt");//open a file complaint.txt
    std::string line; 
    int maxID = 0;

    while (getline(file, line)) {
        std::stringstream ss(line);//convert the line into single stream so we can split it easily
        std::string idStr;
        getline(ss, idStr, '|');

        if (!idStr.empty() && std::all_of(idStr.begin(), idStr.end(), ::isdigit)) {
            int id = std::stoi(idStr);//convert into integer
            if (id > maxID)
                maxID = id;
        }
    }
    return maxID + 1;
}
 //time_t is for timestamps so computer can do calculations easily  both are datatype for storing timestamps
 //tm is used for date time structures 
// Get current date-time as string
std::string getCurrentTimestamp() {
    time_t now = time(0); ///time function gives us timestamps representing current function and time
    tm* local = localtime(&now); //loact time used to convert timestamps into datetimestructures
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);//strftime used to format the date time structures
    return buffer;
}

// Main function to submit complaint
void submitComplaint(const std::string& username) {
    std::ofstream file("complaints.txt", std::ios::app);

    int id = generateComplaintID();
    std::string title, description, category, location;
    int priority;

    std::cin.ignore();//

    std::cout << "\n=== Submit a Complaint ===\n";
    std::cout << "Enter Title: ";
    std::getline(std::cin, title);

    std::cout << "Enter Description: ";
    std::getline(std::cin, description);

    std::cout << "Choose Category:\n";
    std::cout << "1. Infrastructure\n";
    std::cout << "2. Utilities\n";
    std::cout << "3. Environment\n";
    std::cout << "4. Health\n";
    std::cout << "5. Security\n";
    std::cout << "Enter choice: ";
    int catChoice;
    std::cin >> catChoice;

    switch (catChoice) {
        case 1: category = "Infrastructure"; break;
        case 2: category = "Utilities"; break;
        case 3: category = "Environment"; break;
        case 4: category = "Health"; break;
        case 5: category = "Security"; break;
        default: category = "Other"; break;
    }

    std::cout << "Enter Priority (1 - Low to 5 - High): ";
    std::cin >> priority;
    std::cin.ignore();

    std::cout << "Enter Location: ";
    std::getline(std::cin, location);

    std::string timestamp = getCurrentTimestamp();
    std::string status = "Pending";

    // Save complaint in 9-field format (ID|username|title|desc|category|priority|location|timestamp|status)
    file << id << "|" << username << "|" << title << "|" << description << "|"
         << category << "|" << priority << "|" << location << "|" << timestamp << "|" << status << "\n";

    std::cout << "Complaint submitted successfully with ID: " << id << "\n";
}
