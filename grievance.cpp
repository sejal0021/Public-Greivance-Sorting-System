#include "grievance.h"
#include <iostream>

// Default constructor
Grievance::Grievance() {
    id = 0;
    priority = 0;
    status = "Pending";
}

// Parameterized constructor
Grievance::Grievance(int id, const std::string& username, const std::string& title,
                     const std::string& description, const std::string& category,
                     int priority, const std::string& location,
                     const std::string& timestamp, const std::string& status)
    : id(id), username(username), title(title), description(description),
      category(category), priority(priority), location(location),
      timestamp(timestamp), status(status) {}

// Getters
int Grievance::getId() const { return id; }
std::string Grievance::getUsername() const { return username; }
std::string Grievance::getTitle() const { return title; }
std::string Grievance::getDescription() const { return description; }
std::string Grievance::getCategory() const { return category; }
int Grievance::getPriority() const { return priority; }
std::string Grievance::getLocation() const { return location; }
std::string Grievance::getTimestamp() const { return timestamp; }
std::string Grievance::getStatus() const { return status; }

// Setters
void Grievance::setId(int id) { this->id = id; }
void Grievance::setUsername(const std::string& username) { this->username = username; }
void Grievance::setTitle(const std::string& title) { this->title = title; }
void Grievance::setDescription(const std::string& description) { this->description = description; }
void Grievance::setCategory(const std::string& category) { this->category = category; }
void Grievance::setPriority(int priority) { this->priority = priority; }
void Grievance::setLocation(const std::string& location) { this->location = location; }
void Grievance::setTimestamp(const std::string& timestamp) { this->timestamp = timestamp; }
void Grievance::setStatus(const std::string& status) { this->status = status; }

// Display function
void Grievance::display() const {
    std::cout << "\nID: " << id
              << "\nTitle: " << title
              << "\nDescription: " << description
              << "\nCategory: " << category
              << "\nPriority: " << priority
              << "\nLocation: " << location
              << "\nStatus: " << status
              << "\nTimestamp: " << timestamp
              << "\nSubmitted by: " << username
              << "\n------------------------\n";
}
