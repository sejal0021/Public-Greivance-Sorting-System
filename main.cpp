#include <iostream>
#include <string>
#include "user.h"
#include "admin.h"
#include "grievance_submission.h"
#include "grievance_system.h"

void userMenu(const std::string& username) {
    int choice;
    GrievanceSystem system;

    while (true) {
        std::cout << "\n=== USER DASHBOARD ===\n";
        std::cout << "1. Submit New Complaint\n";
        std::cout << "2. Show Complaint System Menu\n";
        std::cout << "0. Logout\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                submitComplaint(username); // username defined & passed
                break;
            case 2:
                system.run(); // Show all complaint dashboard options
                break;
            case 0:
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    int choice;
    std::string username;

    while (true) {
        std::cout << "\n=== PUBLIC GRIEVANCE SORTING SYSTEM ===\n";
        std::cout << "1. Signup\n";
        std::cout << "2. Login as User\n";
        std::cout << "3. Login as Admin\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                if (login(username)) {
                    std::cout << "\nLogin successful! Welcome, " << username << " 🎉\n";
                    userMenu(username);
                }
                break;
            case 3: {
                Admin admin;
                if (admin.login()) {
                    admin.showPanel();
                }
                break;
            }
            case 0:
                std::cout << "Exiting... Thank you!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
