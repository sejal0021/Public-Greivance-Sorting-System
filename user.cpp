#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

bool isValid(const std::string& str) {
    return str.length() >= 8;
}

void signup() {
    std::ofstream file("users.txt", std::ios::app);
    std::string name, username, password;

    std::cin.ignore();
    std::cout << "\n=== USER SIGNUP ===\n";
    std::cout << "Enter your full name: ";
    std::getline(std::cin, name);

    std::cout << "Choose username (min 8 chars): ";
    std::getline(std::cin, username);
    while (!isValid(username)) {
        std::cout << "Username must be at least 8 characters. Try again: ";
        std::getline(std::cin, username);
    }

    std::cout << "Choose password (min 8 chars): ";
    std::getline(std::cin, password);
    while (!isValid(password)) {
        std::cout << "Password must be at least 8 characters. Try again: ";
        std::getline(std::cin, password);
    }

    file << name << "|" << username << "|" << password << "\n";
    std::cout << "Signup successful! You can now login.\n";
}

bool login(std::string& username) {
    std::ifstream file("users.txt");
    std::string inputUser, inputPass;

    std::cin.ignore();
    std::cout << "\n=== USER LOGIN ===\n";
    std::cout << "Enter username: ";
    std::getline(std::cin, inputUser);
    std::cout << "Enter password: ";
    std::getline(std::cin, inputPass);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, storedUser, storedPass;
        getline(ss, name, '|');
        getline(ss, storedUser, '|');
        getline(ss, storedPass, '|');

        if (inputUser == storedUser && inputPass == storedPass) {
            username = name;  // Return user's name
            return true;
        }
    }

    std::cout << "Invalid credentials. Please try again.\n";
    return false;
}
